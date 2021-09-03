#include "Graphics/ModelData/GLwrap/MeshGL.hpp"

#include "Graphics/ModelData/GLwrap/PrimitiveGL.hpp"

using namespace Graphics::Draw;

MeshGL::MeshGL(const Model *model, int index) :
    Mesh(model, index){
}

MeshGL::~MeshGL(){
}

Primitive *MeshGL::_addPrimitive(){
    auto ptr = new PrimitiveGL();
    _primitives.emplace_back(ptr);
    return ptr;
}