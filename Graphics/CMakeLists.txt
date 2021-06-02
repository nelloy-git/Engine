cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES CXX)

include_directories(./include)
include_directories(./glad/include)
include_directories(./glfw/include)

add_subdirectory(./glad)
add_subdirectory(./glfw)

add_library (Graphics STATIC
    ./Window.cpp
)

target_link_libraries(Graphics
    glad
    glfw
)