cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES CXX)

include_directories(./include)
include_directories(./glad/include)
include_directories(./glfw/include)

add_subdirectory(./glad)
add_subdirectory(./glfw)

add_library (${PROJECT_NAME} STATIC
    ./Window.cpp
    ./VBO/Object.cpp
    
    ./GLSL/Shader.cpp
    ./GLSL/Program.cpp
    ./GLSL/Attribute/Base.cpp
    ./GLSL/Attribute/VertexArray.cpp
)

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)