FILE(GLOB Eigen_Eigen2Support_Geometry_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Eigen2Support_Geometry_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Eigen2Support/Geometry)
