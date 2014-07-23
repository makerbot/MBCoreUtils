#!/usr/bin/env python
import os, sys
import json
import copy

# Use our local copy of pystache
sys.path.insert(0, os.path.join(os.path.dirname(os.path.realpath(__file__)), 'lib', 'pystache'))
import pystache

# Specific files, and files in specific folders have special meaning for codegen
# See docs for more info on each.  Be sure not to use these folder/file names in
# MBCoreUtils for things that aren't related to codegen.
TEMPLATES_DIR_NAME = 'templates'
CONTEXT_DIR_NAME = 'contexts'
TRANSFORMATIONS_FILE = 'transformations.json'


def cxt_paths(cxt):
    """
    Recursively walk a supplied dict or list until a value is reached that is not
    a dict or list, and yield that value as well as the path to reach it.
    """
    # TODO(jacksonh) there is probably a more pythonic/efficient way of doing this
    def walk(t):
        def walk_dict(d):
            for k,v in d.iteritems():
                for z in walk(v):
                    parent.append(k)
                    yield z
        def walk_list(l):
            idx = 0
            for i in l:
                for z in walk(i):
                    parent.append(idx)
                    yield z
                idx += 1
        if isinstance(t, dict):
            for z in walk_dict(t):
                yield z
        elif isinstance(t, list):
            for z in walk_list(t):
                yield z
        else:
            yield t

    parent = []
    for endpoint in walk(cxt):
        yield (endpoint, tuple(parent))
        parent = []

def resolve(dict_obj, path):
    return reduce(lambda d, k: d[k] if d and k in d else None, reversed(path), dict_obj)

def replace(context_obj, path, new_val):
    for k in reversed(path[1:]):
        context_obj = context_obj[k]
    context_obj[path[0]] = new_val

def transform(context, transformation_dict):
    """
    Build a new context dict by transforming the supplied context dict
    with the MAPPINGS and TRANSFORMs defined in the supplied transformation_dict
    This is where the magic (aka hacky awfulness) happens.

    @param context: The mustache context dict to transform
    @param transformation_dict: A dict describing operations to perform on the values of specific keys
    """
    keys_with_transform = {}
    new_context = copy.deepcopy(context)

    def search_for_mapping(path_to_key):
        key_name = path_to_key[0]
        parent_path = path_to_key[1:]
        mapping_path = [key_name + "_MAPPINGS"] + parent_path
        resolved = None
        for idx in range(len(parent_path)+1):
            mapping_path = [key_name + "_MAPPINGS"] + parent_path[idx:]
            resolved = resolve(transformation_dict, mapping_path)
            if resolved:
                return resolved

    for endpoint, path in cxt_paths(new_context):
        path_no_indices = [x for x in path if not isinstance(x, int)]
        endpt_key = path_no_indices[0]

        mapping = search_for_mapping(path_no_indices)
        if mapping and endpoint in mapping:
            replace(new_context, path, mapping[endpoint])
        else:
            # Search for a transform
            transform_path = path_no_indices[:]
            transform_path[0] += "_TRANSFORM"
            transform_dict = resolve(transformation_dict, transform_path)
            if transform_dict:
                # Apply name transform if applicable
                if "LAMBDA" in transform_dict and transform_dict["LAMBDA"]:
                    new_name_func = eval(transform_dict["LAMBDA"])
                    new_name = new_name_func(endpoint)
                    replace(new_context, path, new_name)
                    if "REPLACE_MATCHING_VALS_IN_KEYS" in transform_dict and transform_dict["REPLACE_MATCHING_VALS_IN_KEYS"]:
                        # We want to save this transformed name for later
                        # to replace matching endpoints with the specified keys
                        for k in transform_dict["REPLACE_MATCHING_VALS_IN_KEYS"]:
                            if k not in keys_with_transform:
                                keys_with_transform[k] = {}
                            keys_with_transform[k][endpoint] = new_name
            else:
                # No mapping exists for this endpoint, and we're not directly transforming it
                # Check if it has a key that has associated transforms, and if this endpoint equals one of those
                # values that was transformed elsewhere replace our endpoint with that.
                if endpt_key in keys_with_transform and endpoint in keys_with_transform[endpt_key]:
                    replace(new_context, path, keys_with_transform[endpt_key][endpoint])

    if keys_with_transform:
        # Need to regenerate the context paths and iterate over them a second time
        # to ensure no values that need to be replaced were missed.  This could happen
        # if we applied a transformation after iterating over keys listed in it's REPLACE_MATCHING_VALS_IN_KEYS
        for endpoint, path in cxt_paths(new_context):
            endpt_key = path[0]
            if endpt_key in keys_with_transform and endpoint in keys_with_transform[endpt_key]:
                replace(new_context, path, keys_with_transform[endpt_key][endpoint])

    return new_context

def gen_files(env, target, source):
    def get_parent_dirname(node):
        return os.path.split(os.path.dirname(str(node)))[-1]
    def find_dest_in_targets(dirname, filename):
        dest = [t for t in target if dirname == get_parent_dirname(t) and filename == os.path.basename(str(t))]
        if not dest:
            raise Exception('Failed to find expected output {0}/{1} in list of targets passed by SConscript'.format(dirname, filename))
        if len(dest) > 1:
            # There should only be one target with the supplied parent dir and filename
            raise Exception('Too many targets passed by SConscript for destination {0}/{1}'.format(dirname, filename))
        return dest[0]

    templates = []
    original_context = {}
    transformed_contexts = {}
    transformation_meta = {}

    # Populate our template, context and transformation_meta dicts/lists
    for s in source:
        if CONTEXT_DIR_NAME == get_parent_dirname(s):
            with open(str(s), 'r') as f:
                try:
                    original_context.update(json.load(f))
                except Exception as e:
                    raise Exception('Failed to parse context {0} : {1}'.format(str(s), e))

        elif TEMPLATES_DIR_NAME in str(s).split(os.sep):
            templates.append(s)
        elif TRANSFORMATIONS_FILE == os.path.basename(str(s)):
            with open(str(s), 'r') as f:
                try:
                    transformation_meta = json.load(f)
                except Exception as e:
                    raise Exception('Failed to parse transformation.json : {0}'.format(e))

    # Render our templates with the appropriate transformed contexts
    for src_node in templates:
        parent_dirname, filename = get_parent_dirname(src_node), os.path.basename(str(src_node))
        dest_node = find_dest_in_targets(parent_dirname, filename)
        destdir_fullpath = os.path.dirname(str(dest_node))

        if not os.path.exists(destdir_fullpath):
            os.makedirs(destdir_fullpath)

        with open(str(dest_node), 'w') as outf:
            # We use the template's parent directory to select the appropriate transformation meta dict
            if parent_dirname in transformed_contexts:
                template_context = transformed_contexts[parent_dirname]
            elif parent_dirname in transformation_meta:
                template_context = transform(original_context, transformation_meta[parent_dirname])
                transformed_contexts[parent_dirname] = template_context
            else:
                template_context = original_context

            with open(str(src_node), 'r') as in_template:
                try:
                    outf.write(pystache.render(in_template.read(), template_context))
                except Exception as e:
                    raise Exception("Failed to render {0} : {1}".format(str(src_node), e))

                print('Mustache Codegen: Rendered {0}/{1} (tranforms: {2})'.format(parent_dirname, filename, parent_dirname in transformation_meta))
