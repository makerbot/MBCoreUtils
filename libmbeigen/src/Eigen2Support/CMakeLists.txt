FILE(GLOB Eigen_Eigen2Support_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Eigen2Support_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Eigen2Support)

ADD_SUBDIRECTORY(Geometry)
