#include "Data/Mesh.h"

using namespace Graphics::Data;

Mesh::Mesh(const aiMesh *ai_mesh) :
    VBO::Array(Mesh::__getBufferSize(ai_mesh), VBO::UsageType::STATIC){
    
    __count_vertices = ai_mesh->mNumVertices;

    __offset_vertices = 0;
    load(__offset_vertices, __getVerticesSize(ai_mesh), ai_mesh->mVertices);

    __offset_normals = __offset_vertices + __getVerticesSize(ai_mesh);
    load(__offset_normals, __getNormalsSize(ai_mesh), ai_mesh->mNormals);

    __offset_colors = __offset_normals + __getNormalsSize(ai_mesh);
    load(__offset_colors, __getColorsSize(ai_mesh), ai_mesh->mColors[0]);
}

Mesh::~Mesh(){

}

size_t Mesh::__getBufferSize(const aiMesh *ai_mesh){
    size_t s = 0;
    s += __getVerticesSize(ai_mesh);
    s += __getNormalsSize(ai_mesh);
    s += __getColorsSize(ai_mesh);
    return s;
}

size_t Mesh::__getVerticesSize(const aiMesh *ai_mesh){
    return ai_mesh->mNumVertices * sizeof(ai_mesh->mVertices[0]);
}

size_t Mesh::__getNormalsSize(const aiMesh *ai_mesh){
    return ai_mesh->mNumVertices * sizeof(ai_mesh->mNormals[0]);
}

size_t Mesh::__getColorsSize(const aiMesh *ai_mesh){
    return ai_mesh->mNumVertices * sizeof(*ai_mesh->mColors[0]);
}