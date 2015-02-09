FILE(GLOB Eigen_Geometry_arch_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Geometry_arch_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Geometry/arch)
