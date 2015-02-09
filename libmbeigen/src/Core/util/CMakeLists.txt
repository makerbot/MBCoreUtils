FILE(GLOB Eigen_Core_util_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_Core_util_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Core/util)
