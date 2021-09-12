# Install script for directory: /home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen/src/SparseLU" TYPE FILE FILES
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLUImpl.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_Memory.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_Structs.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_Utils.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_column_bmod.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_column_dfs.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_gemm_kernel.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_kernel_bmod.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_panel_bmod.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_panel_dfs.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_pivotL.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_pruneL.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/SparseLU/SparseLU_relax_snode.h"
    )
endif()

