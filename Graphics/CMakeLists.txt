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
    ./Data/glTF.cpp
    ./Data/Material.cpp
    ./Data/Mesh.cpp
    #./Data/Model.cpp
    #./Data/ModelData.cpp
    ./Data/Node.cpp
    ./Data/Primitive.cpp
    #./Data/Scene.cpp
    # ./Data/Texture.cpp

    ./Data/Buffer/BufferCpu.cpp
    ./Data/Buffer/BufferElementGL.cpp
    ./Data/Buffer/BufferVertexGL.cpp

    ./Data/BufferReceiver/gltfReceiver.cpp

    ./Data/Model/gltfModel.cpp

    ./Drawing/Camera.cpp
    ./Drawing/Drawer.cpp

    ./Utils/Log.cpp
)

target_link_libraries(${PROJECT_NAME}
    GraphicsGLwrap
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)
