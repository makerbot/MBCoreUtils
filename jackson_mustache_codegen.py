import argparse
import copy
import imp
import json
import os
import re
import sys
from functools import reduce


# Use our local copy of pystache
sys.path.insert(
    0,
    os.path.join(
        os.path.dirname(os.path.realpath(__file__)),
        'pystache'
    )
)
import pystache

# Lambdas that are available for templates to use. In bw-scons-tools there
# will only be a few, generally available ones.
class _BWLambdas(object):
    def __init__(self, renderer):
        self.renderer = renderer
    def rstrip(self):
        "Remove last character. Useful for removing trailing commas."
        return lambda s: copy.deepcopy(self.renderer).render(s, self.renderer.context)[:-1]
    def snake_to_title(self):
        "Snake case to title."
        return lambda s: copy.deepcopy(self.renderer).render(s, self.renderer.context).title().replace('_', '')


def cxt_paths(cxt):
    """
    Recursively walk a supplied dict or list until a value is reached that is
    not a dict or list, and yield that value as well as the path to reach it.
    """
    # TODO(jacksonh) this can probably be done more efficiently/pythonically
    def walk(t):
        def walk_dict(d):
            for k, v in d.items():
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
    return reduce(
        lambda d, k: d[k] if d and k in d else None,
        reversed(path),
        dict_obj
    )


def replace(context_obj, path, new_val):
    for k in reversed(path[1:]):
        context_obj = context_obj[k]
    context_obj[path[0]] = new_val


def transform_context(context: dict, transformation_dict: dict) -> dict:
    """
    Build a new context dict by transforming the supplied context dict with
    the MAPPINGS, TRANSFORMs, and PATTERNs defined in the supplied transformation_dict
    This is where the magic (aka hacky awfulness) happens.

    @param context: The mustache context dict to transform
    @param transformation_dict: A dict describing operations to mutate the
        values of specific keys.
    """
    keys_with_transform = {}
    new_context = copy.deepcopy(context)

    def search_for_mapping(path_to_key):
        key_name = path_to_key[0]
        parent_path = path_to_key[1:]
        for idx in range(len(parent_path) + 1):
            mapping_path = [key_name + "_MAPPINGS"] + parent_path[idx:]
            resolved = resolve(transformation_dict, mapping_path)
            if resolved:
                return resolved

    def search_for_pattern(path_to_key):
        key_name = path_to_key[0]
        parent_path = path_to_key[1:]
        for idx in range(len(parent_path) + 1):
            pattern_path = [key_name + "_PATTERNS"] + parent_path[idx:]
            resolved = resolve(transformation_dict, pattern_path)
            if resolved:
                return resolved

    for endpoint, path in cxt_paths(new_context):
        path_no_indices = [x for x in path if not isinstance(x, int)]
        endpt_key = path_no_indices[0]
        mapping = search_for_mapping(path_no_indices)
        patterns = search_for_pattern(path_no_indices)
        if (mapping is not None) and endpoint in mapping:
            replace(new_context, path, mapping[endpoint])
        elif (patterns is not None) and any(map(lambda p: re.match(p, endpoint), patterns.keys())):
            # If we have patterns at this context, just try them
            # all and break after we match the first
            for pattern in patterns.keys():
                new_str = re.sub(pattern, patterns[pattern], endpoint)
                if new_str != endpoint:
                    replace(new_context, path, new_str)
                    break

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
                    if ("REPLACE_MATCHING_VALS_IN_KEYS" in transform_dict and
                            transform_dict["REPLACE_MATCHING_VALS_IN_KEYS"]):
                        # We want to save this transformed name for later
                        # to replace matching endpoints with the specified keys
                        for k in transform_dict["REPLACE_MATCHING_VALS_IN_KEYS"]:  # noqa
                            if k not in keys_with_transform:
                                keys_with_transform[k] = {}
                            keys_with_transform[k][endpoint] = new_name
            else:
                # No mapping exists for this endpoint, and we're not directly
                # transforming it.  Check if it has a key that has associated
                # transforms, and if this endpoint equals one of those values
                # that was transformed elsewhere replace our endpoint with that
                if (endpt_key in keys_with_transform and
                        endpoint in keys_with_transform[endpt_key]):
                    replace(new_context,
                            path,
                            keys_with_transform[endpt_key][endpoint])

    if keys_with_transform:
        # Need to regenerate the context paths and iterate over them a second
        # time to ensure no values that need to be replaced were missed.
        # This could happen if we applied a transformation after iterating over
        # keys listed in its REPLACE_MATCHING_VALS_IN_KEYS.
        for endpoint, path in cxt_paths(new_context):
            endpt_key = path[0]
            if (endpt_key in keys_with_transform and
                    endpoint in keys_with_transform[endpt_key]):
                replace(new_context,
                        path,
                        keys_with_transform[endpt_key][endpoint])

    return new_context


def output_file_name(template, output_dir):
    """Calculate the path to the file out be output"""
    return os.path.join(output_dir, os.path.basename(template))


def gen_files(
        templates,
        contexts,
        output_dir,
        transformations_file,
        dynamic_context_args):
    """Generate files from templates & contexts

    @param templates: list of templates to be filled
    @param contexts: a list of context files (.json or .py)
    @param output_dir: the directory that rendered templates are placed in
    @param transformations_file: the path to the transformations json file
    @param dynamic_context_args: dict of arguments to be passed to any
                                 dynamic contexts encountered
    """
    original_context = {}
    # Populate our template, context and transformation_meta dicts/lists
    for context in contexts:
        fname, fext = os.path.splitext(os.path.basename(context))
        if fext == '.py':
            # BIG HACK - enable dynamically generated contexts. This
            # allows us to do hacky machine-specific codegen for things
            # like toolhead structs.
            #
            # We also want to be sure that we do not write bytecode for
            # these files so that we can just glob the entire directory.
            imp.acquire_lock()
            dont_write_bytecode = sys.dont_write_bytecode
            sys.dont_write_bytecode = True
            try:
                dynamic_context = imp.load_source(fname, context)
            except Exception as e:
                raise Exception('Failed to load context {0} : {1}'.format(
                    context, e))
            finally:
                sys.dont_write_bytecode = dont_write_bytecode
                imp.release_lock()
                # Remove any pyc files that we created before this fix
                try:
                    os.remove(context + 'c')
                except OSError:
                    pass
            # separating these try/excepts so no one else spends fifteen
            # minutes debugging why imp.load_source is failing, when it's
            # actually the generation that's failing
            try:
                # dynamic context generators must implement a
                # generate_context(**kwargs) method that returns a dict.
                original_context.update(
                    dynamic_context.generate_context(**dynamic_context_args))
            except Exception as e:
                raise Exception('Failed to generate context from {0} : {1}'
                    .format(context, e))
            print('Mustache Codegen: Loaded dynamic context from: {0}'
                .format(context))
        elif fext == '.json':
            try:
                with open(context, 'r') as f:
                    original_context.update(json.load(f))
            except Exception as e:
                raise Exception('Failed to load context {0} : {1}'.format(
                    context, e))

    transformation_meta = {}
    with open(transformations_file, 'r') as f:
        try:
            transformation_meta = json.load(f)
        except Exception as e:
            raise Exception('Failed to parse {0} : {1}'.format(
                transformations_file, e))

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    transformed_contexts = {}
    # Render our templates with the appropriate transformed contexts
    for template_file in templates:
        parent_dirname = os.path.basename(os.path.dirname(template_file))
        output_file = output_file_name(template_file, output_dir)

        # We use the template's parent directory to select the appropriate
        # transformation meta dict.
        if parent_dirname in transformed_contexts:
            template_context = transformed_contexts[parent_dirname]
        elif parent_dirname in transformation_meta:
            template_context = transform_context(
                original_context,
                transformation_meta[parent_dirname]
            )
            transformed_contexts[parent_dirname] = template_context
        else:
            template_context = original_context

        with open(output_file, 'w') as outf:
            with open(template_file, 'r') as in_template:
                try:
                    renderer = pystache.Renderer()
                    outf.write(
                        renderer.render(
                            in_template.read(),
                            template_context,
                            _BWLambdas(renderer))
                    )
                except Exception as e:
                    raise Exception("Failed to render {0} : {1}".format(
                        template_file, e))

                print('Mustache Codegen: Rendered {0}/{1} (tranforms: {2})'
                      .format(parent_dirname,
                              os.path.basename(template_file),
                              parent_dirname in transformation_meta))


def parse_args(args):
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--templates',
        nargs='+',
        required=True,
        help="Templates to be rendered.")

    parser.add_argument(
        '--contexts',
        nargs='+',
        help="Contexts, used to fill templates.")

    parser.add_argument(
        '--output-dir',
        required=True,
        help="Directory to put rendered templates in.")

    parser.add_argument(
        '--transformations-file',
        help="I'm still unclear on what, exactly, this does.")

    class DynamicContextArgsAction(argparse.Action):
        def __call__(self, parser, namespace, values, option_string=None):
            result = {}
            for value in values:
                try:
                    k, v = value.split('=')
                except ValueError as e:
                    raise Exception(
                        'Incorrectly formatted dynamic context arg: {}'
                        .format(value))
                result[k] = v
            setattr(namespace, self.dest, result)

    parser.add_argument(
        '--dynamic-context-args',
        nargs='+',
        action=DynamicContextArgsAction,
        default={},
        help="Arguments to pass to all dynamic contexts (ARG=value).")

    parser.add_argument(
        '--list-outputs',
        action='store_true',
        help=(
            "Print to stdout a '\\0'-delimited list of files that would be"
            " generated instead of generating them"))

    parsed_args = parser.parse_args(args)

    # argparse can't easily express --flag1 | (--flag2 & --flag3)
    if not parsed_args.list_outputs:
        message = None
        if not parsed_args.contexts and not parsed_args.transformations_file:
            message = (
                "either argument --list-outputs or (--contexts"
                " and --transformations-file) is/are required.")
        elif parsed_args.contexts and not parsed_args.transformations_file:
            message = "--transformations-file required with --contexts"
        elif not parsed_args.contexts and parsed_args.transformations_file:
            message = "--contexts required with --transformations-file"

        if message:
            parser.print_usage()
            print('mustache_codegen.py: error: {}'.format(message))
            sys.exit(2)

    return parsed_args

if __name__ == '__main__':
    args = parse_args(sys.argv[1:])
    if args.list_outputs:
        result = ""
        for template in args.templates:
            if result:
                # I'm using newlines as separators because I can't
                # figure out how to to get cmake to parse \0-delimited
                # lists. Why am I not using semicolon delimiters?
                result += "\n"
            name = output_file_name(template, args.output_dir)
            # Always use posix-style paths. Windows understands them, and
            # they won't be mistaken for escape characters.
            name = re.sub(r'\\', '/', name)
            result += name
        # write to stdout for calling script to consume
        print(result)
    else:
        gen_files(
            args.templates,
            args.contexts,
            args.output_dir,
            args.transformations_file,
            args.dynamic_context_args)
