message("configureing mbcoreutils")
project(MBCoreUtils)

add_custom_command(
    OUTPUT
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error.hh
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
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils)
add_custom_target(bwfiles ALL
    DEPENDS
        ${INCLUDE_OUTPUT_PATH}/bwcoreutils/bot_error.hh
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
