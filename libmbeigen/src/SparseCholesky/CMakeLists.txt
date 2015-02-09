FILE(GLOB Eigen_SparseCholesky_SRCS "*.h")

INSTALL(FILES
  ${Eigen_SparseCholesky_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/SparseCholesky)
