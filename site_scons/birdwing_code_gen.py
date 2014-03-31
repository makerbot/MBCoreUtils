#!/usr/bin/env python

"""
Parses some metafiles into .py and .hh files.  We currently parse two different
types of data: enums and structs.
"""

import copy
import ctypes
import json
import os
import sys

machine_generated_warning = "<-------- This File was Machine Generated by %s, DO NOT MODIFY! -------->\n\n" % (__file__)

def reversedict(adict):
    newdict = {}
    for key, val in adict.iteritems():
        newdict[val] = key
    return newdict 

def gen_python_enum_file(output_path, enum_data):
    with open(output_path, 'w') as f:
        f.write("%s%s" % ("#", machine_generated_warning))
        for group in enum_data:
            f.write("%s = %r\n" % (group , enum_data[group] ))
        if 'error' in enum_data:
            f.write("%s = %r" % ('error_to_string', reversedict(enum_data['error'])))

def make_google_compliant(string):
    string = string.title()
    string = string.replace('_', '')
    return string

def make_human_readable(string):
    string = string.title()
    string = string.replace('_', ' ')
    return string

def gen_cxx_enum_file(output_path, enum_data, namespace, readable = False):
    namespace_top = "namespace " + namespace + " {\n"
    namespace_bottom = "} //namespace"
    guard = os.path.split(output_path)[1].replace('.', '_').upper()
    c_define_top = (
        '#ifndef {guard}\n'
        '#define {guard}\n'
        '#ifndef BRONX\n'
        '#include <string>\n'
        '#include <sstream>\n'
        '#endif\n').format(guard=guard)
    c_define_bottom = "#endif // {}".format(guard)
    stringify_file_top = "#ifndef BRONX\n"
    stringify_file_bottom = "#endif // BRONX\n"

    with open(output_path, 'w') as f:
        for part in [c_define_top, namespace_top]:
            f.write("%s\n" % (part))

        for group in enum_data:
            c_codes = {}
            for key in enum_data[group]:
                c_codes["k%s" % (key)] = enum_data[group][key]
            declaration_top = "enum %s {" % (make_google_compliant(group))
            declaration_middle = ""
            for key, value in enum_data[group].iteritems():
                declaration_middle += "\tk%s = %i,\n" % (make_google_compliant(key), value)
            declaration_bottom = "}; //enum \n"
            for part in [declaration_top, declaration_middle, declaration_bottom]:
                f.write("%s\n" % part)
            c_codes = {}
            for key in enum_data[group]:
                c_codes["k%s" % (key)] = enum_data[group][key]
            if readable:
                stringify_top = "inline std::string stringify_error(int val) {\n\tstd::stringstream retval;\n\tswitch(val){\n"
                stringify_middle = ""
                for key, value in enum_data[group].iteritems():
                    stringify_middle += "\tcase %i:\n\t\tretval << \"%s\";\n\t\tbreak;\n" \
                        % (value, str(make_human_readable(key)))
                stringify_bottom = "\tdefault:\n\t\tretval << \"Unknown Error\";\n\t}\n\treturn retval.str();\n} //stringify"    
            else:
                stringify_top = "inline std::string stringify_%s(%s val) {\n\tstd::stringstream retval;\n\tswitch(val){\n" \
                     % (make_google_compliant(group).lower(), make_google_compliant(group))
                stringify_middle = ""
                for key, value in enum_data[group].iteritems():
                    stringify_middle += "\tcase %i:\n\t\tretval << \"%s::k%s\";\n\t\tbreak;\n" \
                        % (value,namespace,str(make_google_compliant(key)))
                stringify_bottom = "\tdefault:\n\t\tretval << \"%s::Unknown or not implemented\";\n\t}\n\treturn retval.str();\n} //stringify" % (namespace)

            # Stringify
            f.write(stringify_file_top)
            for part in [ stringify_top, stringify_middle, stringify_bottom]:
                f.write("%s\n" % (part))
            f.write(stringify_file_bottom)
        for part in [namespace_bottom, c_define_bottom]:
            f.write("%s\n" % (part))


def gen_files(env, target, source):
    # Name output paths
    if len(target) != 5:
        raise Exception('unexpected number of targets')
    machine_errors_hh = target[0].get_abspath()
    toolhead_errors_hh = target[1].get_abspath()
    all_errors_hh = target[2].get_abspath()
    machine_errors_py = target[3].get_abspath()
    toolhead_errors_py = target[4].get_abspath()

    # Read inputs
    with open(str(source[0])) as f:
        machine_error_data = json.load(f)
    with open(str(source[1])) as f:
        toolhead_error_data = json.load(f)

    machine_enum_data = {
        "error": machine_error_data}
    toolhead_enum_data = {
        "error": toolhead_error_data}

    # combine machine and toolhead errors into a single enum for UI applications
    all_errors_error_data = machine_error_data.copy()
    all_errors_error_data.update(toolhead_error_data)
    all_errors_enum_data = {
        "error": all_errors_error_data}
    machine_filename = "machine_errors"
    toolhead_filename = "toolhead_errors"
    all_errors_filename = "all_errors"

    gen_python_enum_file(machine_errors_py, all_errors_enum_data)
    gen_python_enum_file(toolhead_errors_py, toolhead_enum_data)

    gen_cxx_enum_file(machine_errors_hh, machine_enum_data, "machine")
    gen_cxx_enum_file(toolhead_errors_hh, toolhead_enum_data, "toolhead")
    gen_cxx_enum_file(all_errors_hh, all_errors_enum_data, "bwcoreutils", True)
