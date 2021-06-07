#include "Data/Mesh.h"

#include <memory>

using namespace Graphics::Data;

Mesh::Mesh(const aiMesh *ai_mesh){

    __vao = std::make_unique<GLwrap::VAO>();
    __vao->bind();
    
    __initVBO(ai_mesh);
    __initEBO(ai_mesh);

    __vertices->attrib(0, GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float);

    __vao->unbind();
}

Mesh::~Mesh(){

}

void Mesh::draw(){
    __vao->bind();
    glDrawElements(GL_TRIANGLES, __vertices_count, GL_UNSIGNED_INT, 0);
}

void Mesh::__initVBO(const aiMesh *ai_mesh){

    __vertices_count = ai_mesh->mNumVertices;

    __vertices = std::make_unique<GLwrap::VBO>(__vertices_count * sizeof(ai_mesh->mVertices[0]));
    __vertices->load(ai_mesh->mVertices);

    __normals = std::make_unique<GLwrap::VBO>(__vertices_count * sizeof(ai_mesh->mNormals[0]));
    __normals->load(ai_mesh->mNormals);
    
}

void Mesh::__initEBO(const aiMesh *ai_mesh){
    __faces_count = ai_mesh->mNumFaces;
    
    int offset = 0;
    auto size = 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]);
    __faces = std::make_unique<GLwrap::EBO>(__faces_count * 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]));

    for (int i = 0; i < __faces_count; i++){
        if (ai_mesh->mFaces->mNumIndices != 3){
            throw std::invalid_argument("");
        }

        __faces->load(ai_mesh->mFaces[i].mIndices, offset, size);
        offset += size;
    }
    __faces->bind();
    // __faces.
}

void Mesh::__initVAO(){
    // std::vector<GLwrap::VAOdata> buff_list = {
    //     {GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float, __vertices.get()},
    //     {GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float, __normals.get()},
    //     {GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float, __colors.get()},
    //     {GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::UInt, __faces.get()},
    // };

    // __vao = std::make_unique<GLwrap::VAO>();
    // __vao->attrib(buff_list);
}