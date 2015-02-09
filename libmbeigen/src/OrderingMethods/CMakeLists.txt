FILE(GLOB Eigen_OrderingMethods_SRCS "*.h")

INSTALL(FILES
  ${Eigen_OrderingMethods_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/OrderingMethods)
