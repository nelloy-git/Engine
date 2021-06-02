cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(GLAD LANGUAGES C)

include_directories(./include)
add_library (glad SHARED ./src/glad.c)