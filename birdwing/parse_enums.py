#!/usr/bin/env python

"""
Parses some metafiles into .py and .hh files.  We currently parse two different
types of data: enums and structs.
"""

import argparse
import copy
import ctypes
import json
import os
import sys
import enum_parse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p",
        "--python",
        action="store_true",
        help="export error code file to python"
    )
    parser.add_argument(
        "-c",
        "--clang",
        action="store_true",
        help="export error code file to c"
    )
    args = parser.parse_args()
    cur_dir = os.path.abspath(os.path.dirname(__file__))
    with open(os.path.join(cur_dir, "machine_errors.json")) as f:
        machine_error_data = json.load(f)
    with open(os.path.join(cur_dir, "toolhead_errors.json")) as f:
        toolhead_error_data = json.load(f)
    machine_enum_data = {
        "error": machine_error_data}
    toolhead_enum_data = {
        "error": toolhead_error_data}
    machine_enum_path = cur_dir + "/machine_errors"
    toolhead_enum_path = cur_dir + "/toolhead_errors"

    if args.python:
        print("Parsing Python...")
        enum_parse.parse_enum_python(machine_enum_path, machine_enum_data)
        enum_parse.parse_enum_python(toolhead_enum_path, toolhead_enum_data)
    if args.clang:
        print("Parsing c...")
        enum_parse.parse_enum_c(machine_enum_path, machine_enum_data, "machine")
        enum_parse.parse_enum_c(toolhead_enum_path, toolhead_enum_data, "toolhead")
    if not args.python and not args.clang:
        print("Not parsing anything...")
