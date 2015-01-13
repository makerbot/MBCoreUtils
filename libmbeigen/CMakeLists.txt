include(RegexUtils)
project(libmbeigen)
test_escape_string_as_regex()

file(GLOB Eigen_directory_files "*")

escape_string_as_regex(ESCAPED_CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

foreach(f ${Eigen_directory_files})
  if(NOT ${f} MATCHES "\\.txt" AND NOT ${f} MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/[.].+" AND NOT IS_DIRECTORY ${f})
    list(APPEND Eigen_directory_files_to_install ${f})
  endif()
endforeach()

install_directory(${PROJECT_SOURCE_DIR}/ ${HEADER_INSTALL_DESTINATION}/Eigen)

install(FILES
  ${Eigen_directory_files_to_install}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen COMPONENT Devel)
