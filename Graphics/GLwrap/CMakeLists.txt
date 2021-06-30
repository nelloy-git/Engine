cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(GraphicsGLwrap LANGUAGES CXX)

add_subdirectory(./glad)
add_subdirectory(./glfw)

include_directories(.)
include_directories(../Utils)
include_directories(./glad/include)
include_directories(./glfw/include)

add_library (${PROJECT_NAME} STATIC
    ./GLwrap/Array.cpp
    ./GLwrap/Buffer.cpp
    ./GLwrap/BufferAccessor.cpp
    ./GLwrap/Program.cpp
    ./GLwrap/Shader.cpp
    ./GLwrap/Tex2D.cpp
    ./GLwrap/Types.cpp
    
    ./Context/Keyboard.cpp
    ./Context/Mouse.cpp
    ./Context/Timer.cpp
    ./Context/Window.cpp

    ./Context/glfw/Convert.cpp
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