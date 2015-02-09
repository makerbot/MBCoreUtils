FILE(GLOB Eigen_SuperLUSupport_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_SuperLUSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/SuperLUSupport)
