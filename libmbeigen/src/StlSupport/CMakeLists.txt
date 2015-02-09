FILE(GLOB Eigen_StlSupport_SRCS "*.h")

INSTALL(FILES
  ${Eigen_StlSupport_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/StlSupport)
