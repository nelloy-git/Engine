#include "Model/Mesh.h"

using namespace Graphics::Model;

Mesh::Mesh(){
}

Mesh::~Mesh(){
}

void Mesh::draw(const GLwrap::Program &prog){
    for (auto prim : primitives){
        prim->draw(prog);
    }
}

void Mesh::draw(const GLwrap::Program &prog) const {
    for (auto prim : primitives){
        prim->draw(prog);
    }
}