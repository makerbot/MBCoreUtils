"""
Parses some metafiles into .py and .hh files
"""

import argparse
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

def parse_enum_python(filepath, enum_data):
    pyfilepath = "%s.py" % (filepath)
    with open(pyfilepath, 'w') as f:
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

def parse_enum_c(filepath, filename, enum_data, namespace, stringify, readable = False):
    print("Stringify: {0}".format(stringify))
    cfilepath = "%s.hh" % (filepath)
    #stringifypath = "%s_stringify.cc" % (filepath)
    namespace_top = "namespace " + namespace + " {\n"
    namespace_bottom = "} //namespace"
    c_define_top = "#ifndef %s_HH\n#define %s_HH\n#ifndef BRONX\n#include <string>\n#include <sstream>\n#endif\n" % (filename.upper(), filename.upper())
    c_define_bottom = "#endif // %s_HH" % (filename.upper())
    stringify_file_top = "#ifndef BRONX\n"
    stringify_file_bottom = "#endif // BRONX\n"

    with open(cfilepath, 'w') as f:
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
            if stringify:
                f.write(stringify_file_top)
                for part in [ stringify_top, stringify_middle, stringify_bottom]:
                    f.write("%s\n" % (part))
                f.write(stringify_file_bottom)
        for part in [namespace_bottom, c_define_bottom]:
            f.write("%s\n" % (part))

