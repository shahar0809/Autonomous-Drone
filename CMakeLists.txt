cmake_minimum_required(VERSION 3.10)
project(EXIT_SCAN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(spdlog REQUIRED)
find_package(OpenCV REQUIRED)

# CTello Shared Library =======================================================

add_library(ctello SHARED ctello/src/ctello.cpp)

target_include_directories(ctello PRIVATE ctello/include)

target_link_libraries(ctello PRIVATE spdlog::spdlog)

install(TARGETS ctello DESTINATION ctello/lib)
install(FILES ctello/include/ctello.h DESTINATION ctello/include)

# ORB SLAM2 ===================================================================

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/ORB_SLAM2/cmake_modules)


find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)
find_package(Boost  1.54.0  	     # Minimum or EXACT version e.g. 1.36.0
  REQUIRED             					# Fail with error if Boost is not found
  COMPONENTS serialization 				# Boost libraries by their canonical name
  )   

include_directories(
    ${PROJECT_SOURCE_DIR}/ORB_SLAM2
    ${PROJECT_SOURCE_DIR}/ORB_SLAM2/include
    ${EIGEN3_INCLUDE_DIR}
    ${Pangolin_INCLUDE_DIRS}
)

add_library (${PROJECT_NAME} SHARED
ORB_SLAM2/src/System.cc
ORB_SLAM2/src/Tracking.cc
ORB_SLAM2/src/LocalMapping.cc
ORB_SLAM2/src/LoopClosing.cc
ORB_SLAM2/src/ORBextractor.cc
ORB_SLAM2/src/ORBmatcher.cc
ORB_SLAM2/src/FrameDrawer.cc
ORB_SLAM2/src/Converter.cc
ORB_SLAM2/src/MapPoint.cc
ORB_SLAM2/src/KeyFrame.cc
ORB_SLAM2/src/Map.cc
ORB_SLAM2/src/MapDrawer.cc
ORB_SLAM2/src/Optimizer.cc
ORB_SLAM2/src/PnPsolver.cc
ORB_SLAM2/src/Frame.cc
ORB_SLAM2/src/KeyFrameDatabase.cc
ORB_SLAM2/src/Sim3Solver.cc
ORB_SLAM2/src/Initializer.cc
ORB_SLAM2/src/Viewer.cc
)

target_link_libraries(${PROJECT_NAME}
${OpenCV_LIBS}
${EIGEN3_LIBS}
${PROJECT_SOURCE_DIR}/ORB_SLAM2/Thirdparty/DBoW2/lib/libDBoW2.so
${Pangolin_LIBRARIES}
${PROJECT_SOURCE_DIR}/ORB_SLAM2/Thirdparty/g2o/lib/libg2o.so
${Boost_LIBRARIES}
)

add_executable(video_stream
video_stream.cpp)

target_link_libraries(video_stream ${PROJECT_NAME})
target_include_directories(video_stream PRIVATE ctello/include)

target_link_libraries(video_stream ctello)
target_link_libraries(video_stream ${OpenCV_LIBS})