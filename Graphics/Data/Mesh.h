#pragma once

#include <memory>
#include <stdexcept>

#include "assimp/mesh.h"

#include "Data/Texture.h"

#include "GLwrap/Vao.h"
#include "GLwrap/Vbo.h"
#include "GLwrap/Veo.h"
#include "GLwrap/Tex.h"

namespace Graphics::Data {

// vertices     layout = 0
// normals      layout = 1
class Mesh {
public:
    Mesh(const aiMesh *ai_mesh,
         const std::vector<std::shared_ptr<Texture>> &textures);
    virtual ~Mesh();

    void draw();

    int vertices_count(){return __vertices_count;};

    const int attribute_vertice = 0;
    const int attribute_normal = 1;
    const int attribute_color = 2;

private:
    void __initVBO(const aiMesh *ai_mesh);
    void __initEBO(const aiMesh *ai_mesh);
    void __initTex(const aiMesh *ai_mesh,
                   const std::vector<std::shared_ptr<Texture>> &textures);
    void __initVAO();

    int __vertices_count;
    int __faces_count;
    std::unique_ptr<GLwrap::VBO> __vertices;
    std::unique_ptr<GLwrap::VBO> __normals;
    std::unique_ptr<GLwrap::VBO> __uv;
    std::shared_ptr<GLwrap::Tex2D> __texture;
    
    std::unique_ptr<GLwrap::VEO> __faces;

    std::unique_ptr<GLwrap::VAO> __vao;
};

}