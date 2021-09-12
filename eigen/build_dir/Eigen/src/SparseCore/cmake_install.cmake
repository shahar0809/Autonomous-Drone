# Install script for directory: /home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen/src/SparseCore" TYPE FILE FILES
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/AmbiVector.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/CompressedStorage.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/MappedSparseMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseBlock.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseColEtree.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseCwiseBinaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseCwiseUnaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseDenseProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseDiagonalProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseDot.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseFuzzy.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseMatrixBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparsePermutation.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseRedux.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseSelfAdjointView.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseSparseProductWithPruning.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseTranspose.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseTriangularView.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseUtil.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseVector.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/SparseView.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseCore/TriangularSolver.h"
    )
endif()

