message("configureing mbcoreutils")
project(MBCoreUtils)

add_custom_command(
    OUTPUT
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/machine_errors.hh
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/toolhead_errors.hh
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/all_errors.hh
        ${PROJECT_SOURCE_DIR}/birdwing/machine_errors.py
        ${PROJECT_SOURCE_DIR}/birdwing/toolhead_errors.py
    COMMAND ${PYTHON_EXECUTABLE}
        ${PROJECT_SOURCE_DIR}/birdwing_code_gen.py
        -o ${PROJECT_SOURCE_DIR}/include/bwcoreutils/machine_errors.hh
        -o ${PROJECT_SOURCE_DIR}/include/bwcoreutils/toolhead_errors.hh
        -o ${PROJECT_SOURCE_DIR}/include/bwcoreutils/all_errors.hh
        -o ${PROJECT_SOURCE_DIR}/birdwing/machine_errors.py
        -o ${PROJECT_SOURCE_DIR}/birdwing/toolhead_errors.py
        -i ${PROJECT_SOURCE_DIR}/birdwing/machine_errors.json
        -i ${PROJECT_SOURCE_DIR}/birdwing/toolhead_errors.json
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/include/bwcoreutils/machine_errors.hh ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/include/bwcoreutils/toolhead_errors.hh ${INCLUDE_OUTPUT_PATH}/bwcoreutils
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/include/bwcoreutils/all_errors.hh ${INCLUDE_OUTPUT_PATH}/bwcoreutils)
add_custom_target(bwfiles
    DEPENDS
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/machine_errors.hh
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/toolhead_errors.hh
        ${PROJECT_SOURCE_DIR}/include/bwcoreutils/all_errors.hh
        ${PROJECT_SOURCE_DIR}/birdwing/machine_errors.py
        ${PROJECT_SOURCE_DIR}/birdwing/toolhead_errors.py)
#set_shared(false)
set_shared(true)
install_headers(include/)

