FILE(GLOB Eigen_Core_arch_SSE_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Core_arch_SSE_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Core/arch/SSE)
