cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES CXX)

include_directories(./include)
include_directories(../glad/include)

add_library (Graphics SHARED
    ./Window.cpp
)