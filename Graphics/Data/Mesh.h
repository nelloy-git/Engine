#pragma once

#include <memory>
#include <stdexcept>

#include "assimp/mesh.h"

#include "GLwrap/Ebo.h"
#include "GLwrap/Vao.h"
#include "GLwrap/Vbo.h"

namespace Graphics::Data {

class Mesh {
public:
    Mesh(const aiMesh *ai_mesh);
    virtual ~Mesh();

    void draw();

    int vertices_count(){return __vertices_count;};

    const int attribute_vertice = 0;
    const int attribute_normal = 1;
    const int attribute_color = 2;

private:
    void __initVBO(const aiMesh *ai_mesh);
    void __initEBO(const aiMesh *ai_mesh);
    void __initVAO();

    int __vertices_count;
    int __faces_count;
    std::unique_ptr<GLwrap::VBO> __vertices;
    std::unique_ptr<GLwrap::VBO> __normals;
    std::unique_ptr<GLwrap::VBO> __colors;
    
    std::unique_ptr<GLwrap::EBO> __faces;

    std::unique_ptr<GLwrap::VAO> __vao;
};

}