#include "Draw/ModelData/GLwrap/MeshGL.hpp"

#include "Draw/ModelData/GLwrap/PrimitiveGL.hpp"

using namespace Graphics::Draw;

MeshGL::MeshGL(const Model &model, int index) :
    Mesh(model, index){
}

MeshGL::~MeshGL(){
}

std::shared_ptr<Primitive> MeshGL::addPrimitive(){
    auto prim = std::make_shared<PrimitiveGL>();
    _primitives.push_back(prim);
    return prim;
}