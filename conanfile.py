#  Copyright (c) 2023 UltiMaker B.V.

from os.path import join
from conans import ConanFile, CMake
from pystache_utils import mass_mustache_render
import json
# from .pystache_utils import mass_mustache_render


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
        with open("birdwing_codegen/transformations.json", "r") as ff:
            context_transformations = json.load(ff)
        mass_mustache_render(
            contents_dirs=['birdwing_codegen/templates/machine_cpp'],
            context_dirs=['birdwing_codegen/contexts'],
            context_transform=context_transformations['machine_cpp'],
            output_dir='include/bwcoreutils'
        )
        mass_mustache_render(
            contents_dirs=['birdwing_codegen/templates/shared_cpp'],
            context_dirs=['birdwing_codegen/contexts'],
            context_transform=context_transformations['shared_cpp'],
            output_dir='include/bwcoreutils'
        )


    def build(self):
        self.pystache_generate_birdwing()
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.pystache_generate_birdwing()
        self.copy("include/*.h")
        self.copy("include/*.hh")

    # SS TODO: add linking test via CMake
