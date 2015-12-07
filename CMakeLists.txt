
cmake_minimum_required(VERSION 3.1.0)

project(MBCoreUtils NONE)

find_package(MBCMakeTools REQUIRED)
find_package(Mustache REQUIRED)

# Probably should set individual variables for the individual
# birdwing things, but until then...
set(BIRDWING OFF CACHE BOOL "Toggle building birdwing")
if(${BIRDWING})
    message(FATAL_ERROR "Not set up to build birdwing, yet.")
endif()

set(templates_dir
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/templates")
set(contexts_dir
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts")

mustache_codegen(
    TEMPLATES
        "${templates_dir}/shared_cpp/all_errors.hh"
        "${templates_dir}/shared_cpp/bot_error.hh"
        "${templates_dir}/shared_cpp/bot_error_noqt.hh"
        "${templates_dir}/shared_cpp/ikrpccontroller.hh"
        "${templates_dir}/shared_cpp/kaitenstub.hh"
        "${templates_dir}/shared_cpp/tool_mappings.hh"
        "${templates_dir}/machine_cpp/machine_definitions.hh"
        "${templates_dir}/machine_cpp/machine_errors.hh"
        "${templates_dir}/machine_cpp/machine_structs.hh"
        "${templates_dir}/machine_cpp/toolhead_errors.hh"
        "${templates_dir}/machine_cpp/toolhead_initialization.cc"
        "${templates_dir}/machine_cpp/toolhead_toolidentifier.hh"
    CONTEXTS
        "${contexts_dir}/errors.json"
        "${contexts_dir}/kaiten_api.py"
        "${contexts_dir}/tool_metadata.json"
        "${contexts_dir}/machine_specific_enums.py"
        "${contexts_dir}/machine_specific_toolhead_metadata.py"
    TRANSFORMATIONS_FILE
        "${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json"
    OUTPUT_DIR
        "${PROJECT_BINARY_DIR}/bwcoreutils"
    OUTPUT_VARIABLE
        codegenned_files
)
# Because we don't actually use these files for anything else
add_custom_target(codegen ALL DEPENDS ${codegenned_files})

generate_and_install_config(
    NAME MBCoreUtils
    ADDITIONAL_PATHS
        MBCoreUtils_INCLUDE_DIRS ${HEADER_INSTALL_DIR}
        BWCoreUtils_INCLUDE_DIRS ${HEADER_INSTALL_DIR}/bwcoreutils)

install(
    FILES ${codegenned_files}
    DESTINATION "${HEADER_INSTALL_DIR}/bwcoreutils")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/mbcoreutils"
    DESTINATION "${HEADER_INSTALL_DIR}")

install_docs(
    FILES "${PROJECT_SOURCE_DIR}/README.md"
    PREFIX MBCoreUtils)
