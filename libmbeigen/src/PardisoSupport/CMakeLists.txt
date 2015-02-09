FILE(GLOB Eigen_PardisoSupport_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_PardisoSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/PardisoSupport)
