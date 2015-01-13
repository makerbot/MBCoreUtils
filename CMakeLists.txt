
cmake_minimum_required(VERSION 2.8.3)

project(MBCoreUtils)

find_package(
    MBCMakeTools
    REQUIRED)
setup_environment()

set(
    generated_headers
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

add_custom_command(
    OUTPUT
        ${generated_headers}
    COMMAND ${PYTHON_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/site_scons/mustache_codegen.py
        -contexts ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts
        -templates ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates
        -transformations
            ${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json
    DEPENDS
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts/errors.json
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts/machine_specific_enums.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts/machine_specific_toolhead_metadata.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts/machine_specific_toolhead_structs.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts/tool_metadata.json

        ${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json

        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/machine_definitions.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/machine_errors.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/machine_structs.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/toolhead_errors.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/toolhead_initialization.cc
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/machine_cpp/toolhead_toolidentifier.hh

        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/python/machine_definitions.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/python/machine_errors.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/python/machine_structs.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/python/toolhead_errors.py
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/python/tool_mappings.py

        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/shared_cpp/all_errors.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/shared_cpp/bot_error.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/shared_cpp/bot_error_noqt.hh
        ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/shared_cpp/tool_mappings.hh
        ${PROJECT_SOURCE_DIR}/site_scons/mustache_codegen.py)

add_custom_target(
    bwfiles
    ALL
    DEPENDS ${generated_headers})

install(
    FILES ${generated_headers}
    DESTINATION ${HEADER_INSTALL_DESTINATION}/bwcoreutils)

add_subdirectory(libmbeigen)
