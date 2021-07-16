cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES C CXX)

add_subdirectory(./GLwrap)
add_subdirectory(./Draw)

include_directories(.)
include_directories(./GLwrap)
include_directories(./GLwrap/glad/include)
include_directories(./Utils)
include_directories(./3rdparty/tinygltf)
include_directories(./3rdparty/glm)

add_library (${PROJECT_NAME} STATIC

    #./Drawing/Camera.cpp
    #./Drawing/Drawer.cpp

    ./Utils/Log.cpp
)

target_link_libraries(${PROJECT_NAME}
    GraphicsModel
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)
