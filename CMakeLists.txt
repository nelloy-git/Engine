cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Engine VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Graphics)

include_directories(
    ./include
    ./Graphics
    ./Graphics/3rdparty/glad/include
    ./Graphics/3rdparty/assimp/include
    ./Graphics/3rdparty/glm
)

set(OpenCV_DIR "/usr/local/opencv_3.4.7/share/OpenCV")
find_package(OpenCV REQUIRED)
if (NOT ${OPENCV_FOUND})
    message(SEND_ERROR "Failed to find OpenCV")
    return()
endif()
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(undist undistortion.cpp)
target_link_libraries(undist
    Graphics
    ${OpenCV_LIBRARIES}
)

set_property (TARGET undist
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    Graphics
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)