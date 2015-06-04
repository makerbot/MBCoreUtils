
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
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/templates/shared_cpp")
set(contexts_dir
    "${PROJECT_SOURCE_DIR}/birdwing_codegen/contexts")

mustache_codegen(
    TEMPLATES
        "${templates_dir}/all_errors.hh"
        "${templates_dir}/bot_error.hh"
        "${templates_dir}/bot_error_noqt.hh"
        "${templates_dir}/ikrpccontroller.hh"
        "${templates_dir}/kaitenstub.hh"
        "${templates_dir}/tool_mappings.hh"
    CONTEXTS
        "${contexts_dir}/errors.json"
        "${contexts_dir}/kaiten_api.py"
        "${contexts_dir}/tool_metadata.json"
    TRANSFORMATIONS_FILE
        "${PROJECT_SOURCE_DIR}/birdwing_codegen/transformations.json"
    OUTPUT_DIR
        "${PROJECT_BINARY_DIR}/bwcoreutils"
    OUTPUT_VARIABLE
        codegenned_files
)
# Because we don't actually use these files for anything else
add_custom_target(codegen ALL DEPENDS ${codegenned_files})

include(CMakePackageConfigHelpers)

set(CONFIG_BASENAME "MBCoreUtils")
set(CONFIG_FILENAME "${PROJECT_BINARY_DIR}/${CONFIG_BASENAME}Config.cmake")
set(VERSION_CONFIG_FILENAME
    "${PROJECT_BINARY_DIR}/${CONFIG_BASENAME}ConfigVersion.cmake")

configure_package_config_file(
    "MBCoreUtilsConfig.cmake.in"
    "${CONFIG_FILENAME}"
    INSTALL_DESTINATION "${FINDPACKAGE_CONFIG_INSTALL_DIR}"
    PATH_VARS
        HEADER_INSTALL_DIR
        CONFIG_BASENAME)

write_basic_package_version_file(
    "${VERSION_CONFIG_FILENAME}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(
    FILES
        "${CONFIG_FILENAME}"
        "${VERSION_CONFIG_FILENAME}"
    DESTINATION "${FINDPACKAGE_CONFIG_INSTALL_DIR}")

install(
    FILES ${codegenned_files}
    DESTINATION "${HEADER_INSTALL_DIR}/bwcoreutils")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/mbcoreutils"
    DESTINATION "${HEADER_INSTALL_DIR}")

install_docs(
    FILES "${PROJECT_SOURCE_DIR}/README.md"
    PREFIX MBCoreUtils)
