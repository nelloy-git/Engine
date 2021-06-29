#include "Data/Mesh.h"

#include "Data/ModelData.h"

using namespace Graphics;

Mesh::Mesh(const tinygltf::Model &model,
           const tinygltf::Mesh &mesh,
           ModelData &data){

    for (auto &primitive : mesh.primitives){
        primitives.push_back(std::make_shared<Primitive>(model, primitive, data));
    }
}

Mesh::~Mesh(){

}

void Mesh::draw(){
    for (auto prim : primitives){
        prim->draw();
    }
}

void Mesh::draw() const {
    for (auto prim : primitives){
        prim->draw();
    }
}