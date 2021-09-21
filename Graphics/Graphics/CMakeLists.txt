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

    # ./Render/FragmentShaderGL.cpp
    # ./Render/RendererGL.cpp
    ./Render/Easy/FShader.cpp
    ./Render/Easy/VShader.cpp
    ./Render/Easy/Renderer.cpp

    # ./Model/Material.cpp
    ./Model/Mesh.cpp
    ./Model/Model.cpp
    # ./Model/Render.cpp
    # ./Model/Texture.cpp

    # ./Model/gltf/Primitive.cpp
    ./Model/Loader/TinyGltf/Types.cpp

    ../Utils/Log.cpp
    ./Utils/Transform.cpp
    ./Utils/Camera.cpp

    # ./Render/GLwrap/Default/ShaderInputGLDefault.cpp
    # ./Render/GLwrap/Default/ShaderVertexGLDefault.cpp
    # ./Render/GLwrap/Default/ShaderFragmentGLDefault.cpp

    # ./ModelData/IFaces/Animation.cpp
    # ./ModelData/IFaces/AnimCh.cpp
    # ./ModelData/IFaces/AnimCh/AnimChT.cpp
    # ./ModelData/IFaces/AnimCh/AnimChR.cpp
    # ./ModelData/IFaces/AnimCh/AnimChS.cpp
    # ./ModelData/IFaces/AnimCh/AnimChW.cpp
    # ./ModelData/IFaces/Buffer.cpp
    # ./ModelData/IFaces/Model.cpp
    # ./ModelData/IFaces/Node.cpp

    # ./ModelData/tinygltf/TypesGltf.cpp
    # ./ModelData/tinygltf/ModelLoaderGltf.cpp

    # ./ModelData/GLwrap/BufferGL.cpp
    # ./ModelData/GLwrap/MeshGL.cpp
    # ./ModelData/GLwrap/ModelGL.cpp
    # ./ModelData/GLwrap/PrimitiveGL.cpp
    # ./ModelData/GLwrap/TextureGL.cpp
    # ./ModelData/GLwrap/TypesGL.cpp

    # ./Object.cpp
    # ./ShaderGL.cpp
    # ./Types.cpp

)

target_link_libraries(${PROJECT_NAME}
    GraphicsGLwrap
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++20 standard compliance
    CXX_STANDARD 20
)