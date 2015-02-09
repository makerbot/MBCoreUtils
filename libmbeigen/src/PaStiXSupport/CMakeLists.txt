FILE(GLOB Eigen_PastixSupport_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_PastixSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/PaStiXSupport)
