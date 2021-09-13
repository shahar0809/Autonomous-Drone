# Install script for directory: /home/magshimim/Documents/exit-scan/eigen/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen" TYPE FILE FILES
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Array"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Cholesky"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/CholmodSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Core"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Dense"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Eigen"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Eigen2Support"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Eigenvalues"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Geometry"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Householder"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/IterativeLinearSolvers"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Jacobi"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/LU"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/LeastSquares"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/MetisSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/OrderingMethods"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/PaStiXSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/PardisoSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/QR"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/QtAlignedMalloc"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SPQRSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SVD"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/Sparse"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SparseCholesky"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SparseCore"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SparseLU"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SparseQR"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/StdDeque"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/StdList"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/StdVector"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/SuperLUSupport"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/UmfPackSupport"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/magshimim/Documents/exit-scan/eigen/build_dir/Eigen/src/cmake_install.cmake")

endif()

