message("configureing mbcoreutils")
project(MBCoreUtils)
execute_process(COMMAND ${PYTHON_EXECUTABLE}
    ${PROJECT_SOURCE_DIR}/birdwing_code_gen.py)
execute_process(COMMAND ${PYTHON_EXECUTABLE}
    ./birdwing_code_gen.py -o include/bwcoreutils/machine_errors.hh -o include/bwcoreutils/toolhead_errors.hh -o include/bwcoreutils/all_errors.hh -i include/birdwing/machine_errors.json -i include/birdwing/toolhead_errors.json)
set_shared(false)
install_headers(include/)

