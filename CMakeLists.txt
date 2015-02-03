
cmake_minimum_required(VERSION 2.8.3)

project(MBCoreUtils)

find_package(
    MBCMakeTools
    REQUIRED)
setup_environment()

set(generated_headers
    ${PROJECT_BINARY_DIR}/shared_cpp/bot_error.hh
    ${PROJECT_BINARY_DIR}/shared_cpp/tool_mappings.hh
    ${PROJECT_BINARY_DIR}/shared_cpp/all_errors.hh
    ${PROJECT_BINARY_DIR}/shared_cpp/bot_error_noqt.hh
    ${PROJECT_BINARY_DIR}/machine_cpp/machine_definitions.hh
    ${PROJECT_BINARY_DIR}/machine_cpp/machine_errors.hh
    ${PROJECT_BINARY_DIR}/machine_cpp/machine_structs.hh
    ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_errors.hh
    ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_initialization.cc
    ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_toolidentifier.hh)

set(bw_codegen ${PROJECT_SOURCE_DIR}/birdwing_codegen)
add_custom_command(
    OUTPUT
        ${generated_headers}
    COMMAND ${PYTHON_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/site_scons/mustache_codegen.py
        -contexts ${bw_codegen}/contexts
        -templates ${bw_codegen}/templates
        -transformations ${bw_codegen}/transformations.json
    DEPENDS
        ${bw_codegen}/contexts/errors.json
        ${bw_codegen}/contexts/machine_specific_enums.py
        ${bw_codegen}/contexts/machine_specific_toolhead_metadata.py
        ${bw_codegen}/contexts/machine_specific_toolhead_structs.py
        ${bw_codegen}/contexts/tool_metadata.json

        ${bw_codegen}/transformations.json

        ${bw_codegen}/templates/machine_cpp/machine_definitions.hh
        ${bw_codegen}/templates/machine_cpp/machine_errors.hh
        ${bw_codegen}/templates/machine_cpp/machine_structs.hh
        ${bw_codegen}/templates/machine_cpp/toolhead_errors.hh
        ${bw_codegen}/templates/machine_cpp/toolhead_initialization.cc
        ${bw_codegen}/templates/machine_cpp/toolhead_toolidentifier.hh

        ${bw_codegen}/templates/python/machine_definitions.py
        ${bw_codegen}/templates/python/machine_errors.py
        ${bw_codegen}/templates/python/machine_structs.py
        ${bw_codegen}/templates/python/toolhead_errors.py
        ${bw_codegen}/templates/python/tool_mappings.py

        ${bw_codegen}/templates/shared_cpp/all_errors.hh
        ${bw_codegen}/templates/shared_cpp/bot_error.hh
        ${bw_codegen}/templates/shared_cpp/bot_error_noqt.hh
        ${bw_codegen}/templates/shared_cpp/tool_mappings.hh
        ${PROJECT_SOURCE_DIR}/site_scons/mustache_codegen.py)

add_custom_target(
    bwfiles
    ALL
    DEPENDS ${generated_headers})

install(
    FILES ${generated_headers}
    DESTINATION ${HEADER_INSTALL_DESTINATION}/bwcoreutils)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/mbcoreutils
    DESTINATION ${HEADER_INSTALL_DESTINATION})

add_subdirectory(libmbeigen)
