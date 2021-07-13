cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Engine VERSION 0.1 LANGUAGES CXX)

if (WIN32)
    set(CMAKE_CXX_COMPILER C:/MinGW/mingw64/bin/g++.exe)
    set(CMAKE_C_COMPILER C:/MinGW/mingw64/bin/gcc.exe)
else ()
    set(/usr/bin/g++-9.exe)
    set(/usr/bin/gcc-9.exe)
endif (WIN32)

#set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_subdirectory(Graphics)

include_directories(
    ./include
    ./Graphics
    ./Graphics/Utils
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
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)