cmake_minimum_required(VERSION 3.1...3.17 FATAL_ERROR)

project(Graphics LANGUAGES CXX)

add_subdirectory(./GLwrap)
add_subdirectory(./3rdparty/assimp)

include_directories(.)
include_directories(./GLwrap)
include_directories(./3rdparty/assimp/include)
include_directories(./3rdparty/glm)
include_directories(./3rdparty/stb)

add_library (${PROJECT_NAME} STATIC
    ./Data/AssimpImporter.cpp
    ./Data/Mesh.cpp
    ./Data/Model.cpp
    ./Data/Texture.cpp
)

target_link_libraries(${PROJECT_NAME}
    GraphicsGLwrap
    assimp
)

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)
[submodule ".\\Graphics\\3rdparty\\assimp"]
	url = https://github.com/assimp/assimp.git
	active = true
[submodule ".\\Graphics\\3rdparty\\stb"]
	url = https://github.com/nothings/stb.git
	active = true