cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Engine VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Graphics)

include_directories(
    ./include
    ./Graphics
    ./Graphics/GLwrap
    ./Graphics/GLwrap/glad/include
    ./Graphics/3rdparty/glm
    ./Graphics/3rdparty/tinygltf
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