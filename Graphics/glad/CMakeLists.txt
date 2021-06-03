cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(GLAD LANGUAGES C)

include_directories(./include)
add_library (glad SHARED
    ./src/glad.c
)

# GENERATE_EXPORT_HEADER(glad           
#     BASE_NAME glad
#     EXPORT_MACRO_NAME GLAPI
#     EXPORT_FILE_NAME glad.h
#     STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)