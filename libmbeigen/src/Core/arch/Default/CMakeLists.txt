FILE(GLOB Eigen_Core_arch_Default_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Core_arch_Default_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Core/arch/Default)
