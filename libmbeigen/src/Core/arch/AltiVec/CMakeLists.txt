FILE(GLOB Eigen_Core_arch_AltiVec_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Core_arch_AltiVec_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Core/arch/AltiVec)
