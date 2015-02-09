FILE(GLOB Eigen_plugins_SRCS "*.h")

INSTALL(FILES
  ${Eigen_plugins_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/plugins)
