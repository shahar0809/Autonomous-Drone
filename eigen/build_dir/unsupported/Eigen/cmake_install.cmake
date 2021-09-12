# Install script for directory: /home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/AdolcForward"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/AlignedVector3"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/ArpackSupport"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/AutoDiff"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/BVH"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/FFT"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/IterativeSolvers"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/KroneckerProduct"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/LevenbergMarquardt"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/MatrixFunctions"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/MoreVectorization"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/MPRealSupport"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/NonLinearOptimization"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/NumericalDiff"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/OpenGLSupport"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/Polynomials"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/Skyline"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/SparseExtra"
    "/home/magshimim/Documents/exit-scan/eigen/unsupported/Eigen/Splines"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/magshimim/Documents/exit-scan/eigen/build_dir/unsupported/Eigen/src/cmake_install.cmake")

endif()

