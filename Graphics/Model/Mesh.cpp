#include "Model/Mesh.h"

using namespace Graphics::Model;

Mesh::Mesh(){
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