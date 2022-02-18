cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Engine VERSION 0.1 LANGUAGES CXX)

# add_compile_options(-g -O0)

add_subdirectory(./3rdparty/glwpp)
include_directories(
    ./include
    ./3rdparty/glwpp/include
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    glwpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)