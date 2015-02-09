FILE(GLOB Eigen_SparseCore_SRCS "*.h")

INSTALL(FILES 
  ${Eigen_SparseCore_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/SparseCore)
