#pragma once

#include "assimp/mesh.h"

#include "VBO/Array.h"

namespace Graphics::Data {

class Mesh : public VBO::Array {
public:
    Mesh(const aiMesh *ai_mesh);
    virtual ~Mesh();

    int count_vertices(){return __count_vertices;};

    int offset_vertices(){return __offset_vertices;};
    int offset_normals(){return __offset_normals;};
    int offset_colors(){return __offset_colors;};

    size_t size_vertices(){return __size_vertices;};
    size_t size_normals(){return __size_normals;};
    size_t size_colors(){return __size_colors;};

private:
    static size_t __getBufferSize(const aiMesh *ai_mesh);
    static size_t __getVerticesSize(const aiMesh *ai_mesh);
    static size_t __getNormalsSize(const aiMesh *ai_mesh);
    static size_t __getColorsSize(const aiMesh *ai_mesh);

    int __count_vertices;

    int __offset_vertices;
    int __offset_normals;
    int __offset_colors;

    size_t __size_vertices;
    size_t __size_normals;
    size_t __size_colors;
};

}