message("configureing mbcoreutils")
cmake_minimum_required(VERSION 2.8.3)
project(MBCoreUtils)
set(utils ${CMAKE_SOURCE_DIR}/../../mw-cmake-tools/utils.cmake)
if(EXISTS "${utils}")
    include("../../mw-cmake-tools/utils.cmake")
    set(TR_BUILD true)
else()
    include("build/mw-cmake-tools/utils.cmake")
endif()
setup_environment()

add_custom_command(
    OUTPUT
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error_noqt.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/tool_mappings.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/all_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_toolidentifier.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_initialization.cc
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_structs.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_definitions.hh
    COMMAND ${PYTHON_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/site_scons/mustache_codegen.py
        -contexts ${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts
        -templates ${PROJECT_SOURCE_DIR}/birdwing_codegen/templates
        -transformations
            ${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/shared_cpp/bot_error.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/shared_cpp/tool_mappings.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/shared_cpp/all_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/shared_cpp/bot_error_noqt.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/machine_definitions.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/machine_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/machine_structs.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_initialization.cc
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/machine_cpp/toolhead_toolidentifier.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils
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
)
add_custom_target(bwfiles ALL
    DEPENDS
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error_noqt.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/tool_mappings.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/all_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_toolidentifier.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_initialization.cc
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/toolhead_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_structs.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_errors.hh
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/machine_definitions.hh)
install_headers(include/)

add_subdirectory(libmbeigen)
