FILE(GLOB Eigen_Cholesky_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Cholesky_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Cholesky)
