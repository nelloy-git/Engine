cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES CXX)

include_directories(.)
include_directories(./3rdparty/glad/include)
include_directories(./3rdparty/glfw/include)
include_directories(./3rdparty/assimp/include)
include_directories(./3rdparty/glm)
include_directories(./3rdparty/stb)

add_subdirectory(./3rdparty/assimp)
add_subdirectory(./3rdparty/glad)
add_subdirectory(./3rdparty/glfw)

add_library (${PROJECT_NAME} STATIC
    ./Window.cpp

    ./GLwrap/Buffer.cpp
    ./GLwrap/Shader.cpp
    ./GLwrap/Program.cpp
    ./GLwrap/Vao.cpp
    ./GLwrap/Tex.cpp
    ./GLwrap/Types.cpp

    ./Data/AssimpImporter.cpp
    ./Data/Mesh.cpp
    ./Data/Model.cpp
    ./Data/Texture.cpp
)

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    assimp
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)