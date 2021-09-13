# Install script for directory: /home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen/src/Core" TYPE FILE FILES
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Array.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/ArrayBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/ArrayWrapper.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Assign.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Assign_MKL.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/BandMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Block.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/BooleanRedux.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CommaInitializer.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CoreIterators.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CwiseBinaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CwiseNullaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CwiseUnaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/CwiseUnaryView.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/DenseBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/DenseCoeffsBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/DenseStorage.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Diagonal.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/DiagonalMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/DiagonalProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Dot.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/EigenBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Flagged.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/ForceAlignedAccess.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Functors.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Fuzzy.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/GeneralProduct.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/GenericPacketMath.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/GlobalFunctions.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/IO.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Map.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/MapBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/MathFunctions.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Matrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/MatrixBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/NestByValue.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/NoAlias.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/NumTraits.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/PermutationMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/PlainObjectBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/ProductBase.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Random.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Redux.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Ref.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Replicate.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/ReturnByValue.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Reverse.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Select.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/SelfAdjointView.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/SelfCwiseBinaryOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/SolveTriangular.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/StableNorm.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Stride.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Swap.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Transpose.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Transpositions.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/TriangularMatrix.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/VectorBlock.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/VectorwiseOp.h"
    "/home/magshimim/Documents/exit-scan/eigen/Eigen/src/Core/Visitor.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/magshimim/Documents/exit-scan/eigen/build_dir/Eigen/src/Core/products/cmake_install.cmake")
  include("/home/magshimim/Documents/exit-scan/eigen/build_dir/Eigen/src/Core/util/cmake_install.cmake")
  include("/home/magshimim/Documents/exit-scan/eigen/build_dir/Eigen/src/Core/arch/cmake_install.cmake")

endif()

