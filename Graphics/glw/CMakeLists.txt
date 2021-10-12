cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(glw LANGUAGES CXX)

add_subdirectory(./glad)
add_subdirectory(./glfw)
add_subdirectory(./magic_enum)

include_directories(.)
include_directories(./glad/include)
include_directories(./glfw/include)
include_directories(./magic_enum/include)

add_library (${PROJECT_NAME} STATIC
    # ./glw/Array.cpp
    # ./glw/Buffer.cpp
    # ./glw/Program.cpp
    # ./glw/Shader.cpp
    # ./glw/Tex2D.cpp
    
    ./Context/Keyboard.cpp
    ./Context/Mouse.cpp
    ./Context/Timer.cpp
    ./Context/Window.cpp

    ./Context/glfw/Convert.cpp
)

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    magic_enum
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)