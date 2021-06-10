cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES C CXX)

add_subdirectory(./GLwrap)

include_directories(.)
include_directories(./GLwrap)
include_directories(./Utils)
include_directories(./GLwrap/glad/include)
include_directories(./3rdparty/tinygltf)
include_directories(./3rdparty/glm)

add_library (${PROJECT_NAME} STATIC
    ./Data/Mesh_glTF.cpp
    ./Data/Model_glTF.cpp
    ./Data/Primitive_glTF.cpp
    # ./Data/Texture.cpp

    ./Utils/Log.cpp
)

target_link_libraries(${PROJECT_NAME}
    GraphicsGLwrap
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)
