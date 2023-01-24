#  Copyright (c) 2023 UltiMaker B.V.

from os.path import join
from conans import ConanFile, CMake
from pystache_utils import mass_mustache_render
# from .pystache_utils import mass_mustache_render


required_conan_version = ">=1.56.0"

class MBCoreUtilsConan(ConanFile):
    name = "mb_core_utils"
    version = "0.1"
    exports = \
        "pystache_utils.py", \
        "birdwing_codegen/contexts/*.json", \
        "birdwing_codegen/templates/machine_cpp/*.hh", \
        "birdwing_codegen/templates/shared_cpp/*.hh"
    exports_sources = "include/mbcoreutils/*.h"

    def pystache_generate_birdwing(self):
        content_dirs = [
            join(self.source_folder, 'birdwing_codegen/templates/machine_cpp'),
            join(self.source_folder, 'birdwing_codegen/templates/shared_cpp')
        ]
        context_dirs = [
            join(self.source_folder, 'birdwing_codegen/contexts')
        ]
        mustache_generated_outdir = join(self.source_folder, 'include/bwcoreutils')
        mass_mustache_render(
            content_dirs,
            context_dirs,
            mustache_generated_outdir
        )

    def build(self):
        self.pystache_generate_birdwing()
        # cmake = CMake(self)
        # cmake.configure()
        # cmake.build()

    def package(self):
        self.pystache_generate_birdwing()
        self.copy("include/*.h")
        self.copy("include/*.hh")

    # SS todo: add linking test via CMake
