FILE(GLOB Eigen_Core_Product_SRCS "*.h")

INSTALL(FILES
  ${Eigen_Core_Product_SRCS}
  DESTINATION ${HEADER_INSTALL_DESTINATION}/Eigen/src/Core/products)
