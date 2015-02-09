FILE(GLOB Eigen_IterativeLinearSolvers_SRCS "*.h")

INSTALL(FILES
  ${Eigen_IterativeLinearSolvers_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/IterativeLinearSolvers)
