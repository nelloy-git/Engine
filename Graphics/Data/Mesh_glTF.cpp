#include "Data/Mesh_glTF.h"

#include <memory>

#include "Utils/Log.h"

using namespace Graphics;
using namespace GLwrap;



Mesh_glTF::Mesh_glTF(const tinygltf::Model &model, const tinygltf::Mesh &mesh){
    for (auto &primitive : mesh.primitives){
        __primitives.push_back(std::make_shared<Primitive_glTF>(model, primitive));
    }
}

Mesh_glTF::~Mesh_glTF(){

}

void Mesh_glTF::draw(){
    for (auto primitive : __primitives){
        primitive->draw();
    }
}