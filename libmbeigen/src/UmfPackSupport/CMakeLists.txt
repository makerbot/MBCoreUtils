FILE(GLOB Eigen_UmfPackSupport_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_UmfPackSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/UmfPackSupport)
