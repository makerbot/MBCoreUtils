
cmake_minimum_required(VERSION 3.1.0)

project(MBCoreUtils NONE)

find_package(MBCMakeTools REQUIRED)
find_package(Mustache REQUIRED)

get_header_prefix_root(header_install_root)

set(templates_dir
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/templates")
set(contexts_dir
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts")

set(_CONTEXTS
    "${contexts_dir}/errors.json"
    "${contexts_dir}/tool_metadata.json"
    "${contexts_dir}/machine_specific_enums.json")


if(${BIRDWING})
    if(${MB_CROSS})
        set(ROOT rootfs)
    else()
        set(ROOT host)
    endif()
    set(python_install_dir "${ROOT}/${LIB_INSTALL_DIR}/python3.4/mbcoreutils")
    set(static_birdwing_dir
        "${PROJECT_SOURCE_DIR}/birdwing_codegen/static")
    install(FILES
        "${static_birdwing_dir}/machine_config_skeleton.json"
        DESTINATION "${ROOT}/usr/settings")
    mustache_codegen(
        TEMPLATES
            "${templates_dir}/python/common_settings.py"
            "${templates_dir}/python/machine_definitions.py"
            "${templates_dir}/python/machine_errors.py"
            "${templates_dir}/python/toolhead_errors.py"
            "${templates_dir}/python/tool_mappings.py"
        CONTEXTS
            "${_CONTEXTS}"
        TRANSFORMATIONS_FILE
            "${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json"
        OUTPUT_DIR
            "${PROJECT_BINARY_DIR}/python_codegen"
        OUTPUT_VARIABLE
            codegenned_files_python)
    add_custom_target(python_codgen ALL DEPENDS ${codegenned_files_python})
    install(
        FILES ${codegenned_files_python}
        DESTINATION ${python_install_dir})
endif()

mustache_codegen(
    TEMPLATES
        "${templates_dir}/shared_cpp/all_errors.hh"
        "${templates_dir}/shared_cpp/all_errors_node.hh"
        "${templates_dir}/shared_cpp/bot_error.hh"
        "${templates_dir}/shared_cpp/bot_error_noqt.hh"
        "${templates_dir}/shared_cpp/bot_error_translateable.hh"
        "${templates_dir}/shared_cpp/common_settings.hh"
        "${templates_dir}/shared_cpp/tool_mappings.hh"
        "${templates_dir}/machine_cpp/machine_definitions.hh"
        "${templates_dir}/machine_cpp/machine_errors.hh"
        "${templates_dir}/machine_cpp/toolhead_errors.hh"
        "${templates_dir}/machine_cpp/toolhead_toolidentifier.hh"
    CONTEXTS
        "${_CONTEXTS}"
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
        MBCoreUtils_INCLUDE_DIRS
            ${header_install_root}${HEADER_INSTALL_DIR}
        BWCoreUtils_INCLUDE_DIRS
            ${header_install_root}${HEADER_INSTALL_DIR}/bwcoreutils)

install(
    FILES ${codegenned_files}
    DESTINATION "${header_install_root}${HEADER_INSTALL_DIR}/bwcoreutils")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/mbcoreutils"
    DESTINATION "${header_install_root}${HEADER_INSTALL_DIR}")

if(NOT DEFINED BIRDWING)
    install_docs(
        FILES "${PROJECT_SOURCE_DIR}/README.md"
        PREFIX MBCoreUtils)
endif()
