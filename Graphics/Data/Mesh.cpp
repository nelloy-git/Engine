#include "Data/Mesh.h"

using namespace Graphics;

Mesh::Mesh(const tinygltf::Model &model,
           const tinygltf::Mesh &mesh,
           const ModelData &buffer){

    for (auto &primitive : mesh.primitives){
        primitives.push_back(std::make_shared<Primitive>(model, primitive, buffer));
    }
}

Mesh::~Mesh(){

}

void Mesh::draw(){
    for (auto prim : primitives){
        prim->draw();
    }
}