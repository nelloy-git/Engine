cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Engine VERSION 0.1 LANGUAGES CXX)

add_subdirectory(Graphics)

include_directories(
    ./include
    ./Graphics/include
    ./Graphics/glad/include
)

add_executable(main main.cpp)
target_link_libraries(main
    Graphics
)