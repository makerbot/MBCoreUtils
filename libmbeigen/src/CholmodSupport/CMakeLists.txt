FILE(GLOB Eigen_CholmodSupport_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_CholmodSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/CholmodSupport)
