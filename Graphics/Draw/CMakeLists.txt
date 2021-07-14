cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(GraphicsModel LANGUAGES CXX)

include_directories(..)
include_directories(../GLwrap)
include_directories(../GLwrap/glad/include)
include_directories(../GLwrap/glfw/include)
include_directories(../Utils)
include_directories(../3rdparty/tinygltf)
include_directories(../3rdparty/glm)

add_library (${PROJECT_NAME} STATIC
    ./Loader/Loader.cpp

    ./Loader/fromGltf/gltf.cpp
    ./Loader/fromGltf/LoaderGltf.cpp

    ./Loader/toGLwrap/BufferGLwrap.cpp
    ./Loader/toGLwrap/IniterGLwrap.cpp
    ./Loader/toGLwrap/ModelGLwrap.cpp
    ./Loader/toGLwrap/PrimitiveGLwrap.cpp
    ./Loader/toGLwrap/ShaderGLwrap.cpp
    ./Loader/toGLwrap/TextureGLwrap.cpp
    ./Loader/toGLwrap/TypesGLwrap.cpp

    ./BufferCpu.cpp
    ./Material.cpp
    ./Mesh.cpp
    ./Model.cpp
    ./Node.cpp
    ./Scene.cpp
    ./Types.cpp
)

target_link_libraries(${PROJECT_NAME}
    GraphicsGLwrap
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)