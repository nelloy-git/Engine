#include "Data/Mesh.h"

#include <memory>

using namespace Graphics::Data;

Mesh::Mesh(const aiMesh *ai_mesh, 
           const std::vector<std::shared_ptr<Texture>> &textures){
    __vao = std::make_unique<GLwrap::VAO>();
    __vao->bind();
    
    __initVBO(ai_mesh);
    __initEBO(ai_mesh);
    __initTex(ai_mesh, textures);

    __vertices->attrib(0, GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float);
    __normals->attrib(1, GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float);
    __uv->attrib(2, GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float);

    __vao->unbind();
}

Mesh::~Mesh(){

}

void Mesh::draw(){
    __vao->bind();

    glActiveTexture(GL_TEXTURE0);
    __texture->bind();

    glDrawElements(GL_TRIANGLES, 3 * __faces_count, GL_UNSIGNED_INT, 0);
}

void Mesh::__initVBO(const aiMesh *ai_mesh){

    __vertices_count = ai_mesh->mNumVertices;

    __vertices = std::make_unique<GLwrap::VBO>(__vertices_count * sizeof(ai_mesh->mVertices[0]));
    __vertices->load(ai_mesh->mVertices);

    __normals = std::make_unique<GLwrap::VBO>(__vertices_count * sizeof(ai_mesh->mNormals[0]));
    __normals->load(ai_mesh->mNormals);

    __uv = std::make_unique<GLwrap::VBO>(__vertices_count * sizeof(ai_mesh->mTextureCoords[0][0]));
    __uv->load(ai_mesh->mTextureCoords[0]);
    
}

void Mesh::__initEBO(const aiMesh *ai_mesh){
    __faces_count = ai_mesh->mNumFaces;
    
    int offset = 0;
    auto size = 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]);
    __faces = std::make_unique<GLwrap::VEO>(__faces_count * 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]));

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

void Mesh::__initTex(const aiMesh *ai_mesh, 
                     const std::vector<std::shared_ptr<Texture>> &textures){

    int pos = ai_mesh->mMaterialIndex;
    auto data = textures[pos];

    __texture = std::make_shared<GLwrap::Tex2D>();

    printf("%s\n", data->path.c_str());

    __texture->load(data->width, data->height, data->data.get());
}