#  Copyright (c) 2023 UltiMaker B.V.

import os
from conans import ConanFile, CMake
from pystache_utils import mass_mustache_render, get_files_from_dir
import json


required_conan_version = ">=1.56.0"

class MBCoreUtilsConan(ConanFile):
    settings = "build_type"
    name = "mb_core_utils"
    version = "0.1"
    requires = "jsoncpp/[>=1.9.5]"
    exports = [
        "pystache_utils.py",
        "jackson_mustache_codegen.py",
        "birdwing_codegen/transformations.json",
        "birdwing_codegen/contexts/*.json",
        "birdwing_codegen/templates/machine_cpp/*.hh",
        "birdwing_codegen/templates/shared_cpp/*.hh",
        "CMakeLists.txt"
    ]
    exports_sources = "include/mbcoreutils/*.h"
    generators = "CMakeDeps"

    def pystache_generate_birdwing(self):
        contexts = [
            "birdwing_codegen/contexts/errors.json",
            "birdwing_codegen/contexts/tool_metadata.json",
            "birdwing_codegen/contexts/machine_specific_enums.json",
            "birdwing_codegen/contexts/common_settings.json"
        ]
        conanfile_script_dir = os.path.dirname(__file__)
        context_paths = [os.path.join(conanfile_script_dir, foo) for foo in contexts]
        transform_file_path = os.path.join(conanfile_script_dir, "birdwing_codegen/transformations.json")
        with open(transform_file_path, "r") as ff:
            context_transformations = json.load(ff)
        #
        machine_cpp_templates_dir = os.path.join(conanfile_script_dir, "birdwing_codegen/templates/machine_cpp")
        machine_cpp_templates = get_files_from_dir(
            machine_cpp_templates_dir,
            extension=".hh"
        )
        bwcoreutils_dir = os.path.join(conanfile_script_dir, "include/bwcoreutils")
        mass_mustache_render(
            template_paths=machine_cpp_templates,
            context_paths=context_paths,
            context_transform=context_transformations['machine_cpp'],
            output_dir=bwcoreutils_dir
        )
        #
        shared_cpp_templates_dir = os.path.join(conanfile_script_dir, "birdwing_codegen/templates/shared_cpp")
        shared_cpp_templates = get_files_from_dir(
            shared_cpp_templates_dir,
            extension=".hh"
        )
        mass_mustache_render(
            template_paths=shared_cpp_templates,
            context_paths=context_paths,
            context_transform=context_transformations['shared_cpp'],
            output_dir=bwcoreutils_dir
        )


    def build(self):
        self.pystache_generate_birdwing()
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("include/*.h")
        self.copy("include/*.hh")

    # SS TODO: add linking test via CMake
