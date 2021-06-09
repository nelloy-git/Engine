#include "Data/Mesh.h"

#include <memory>

using namespace GLwrap;
using namespace Graphics::Data;

Mesh::Mesh(const aiMesh *ai_mesh, 
           const std::vector<std::shared_ptr<Texture>> &textures){
               
    __initVBO(ai_mesh);
    __initEBO(ai_mesh);
    __initTex(ai_mesh, textures);
    __initVAO();
}

Mesh::~Mesh(){

}

void Mesh::draw(){
    __vao->bind();

    glActiveTexture(GL_TEXTURE0);
    __texture->bind();

    glDrawElements(GL_TRIANGLES, 3 * __faces_count, GL_UNSIGNED_INT, 0);
    __vao->unbind();
}

void Mesh::__initVBO(const aiMesh *ai_mesh){

    __vertices_count = ai_mesh->mNumVertices;

    __vertices = std::make_shared<VBO>(__vertices_count * sizeof(ai_mesh->mVertices[0]));
    __vertices->load(ai_mesh->mVertices);

    __normals = std::make_shared<VBO>(__vertices_count * sizeof(ai_mesh->mNormals[0]));
    __normals->load(ai_mesh->mNormals);

    __uv = std::make_shared<VBO>(__vertices_count * sizeof(ai_mesh->mTextureCoords[0][0]));
    __uv->load(ai_mesh->mTextureCoords[0]);
    
}

void Mesh::__initEBO(const aiMesh *ai_mesh){
    __faces_count = ai_mesh->mNumFaces;
    
    int offset = 0;
    auto size = 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]);
    __faces = std::make_shared<VEO>(__faces_count * 3 * sizeof(ai_mesh->mFaces[0].mIndices[0]));

    for (int i = 0; i < __faces_count; i++){
        if (ai_mesh->mFaces->mNumIndices != 3){
            throw std::invalid_argument("");
        }

        __faces->load(ai_mesh->mFaces[i].mIndices, offset, size);
        offset += size;
    }
}

void Mesh::__initVAO(){
    __vao = std::make_shared<VAO>();

    VAO::AttrList list;

    auto attr_vert = std::make_shared<VBO::Attrib>(layout_vertice, ShaderDataSize::Vec3, ShaderDataType::Float);
    list.push_back({__vertices, attr_vert});

    auto attr_norm = std::make_shared<VBO::Attrib>(layout_normal, ShaderDataSize::Vec3, ShaderDataType::Float);
    list.push_back({__normals, attr_norm});

    auto attr_uv = std::make_shared<VBO::Attrib>(layout_uv, ShaderDataSize::Vec3, ShaderDataType::Float);
    list.push_back({__uv, attr_uv});

    __vao->load(list, __faces);
}

void Mesh::__initTex(const aiMesh *ai_mesh, 
                     const std::vector<std::shared_ptr<Texture>> &textures){

    int pos = ai_mesh->mMaterialIndex;
    auto data = textures[pos];

    __texture = std::make_shared<Tex2D>();
    __texture->load(data->data.get(), data->width, data->height);
}