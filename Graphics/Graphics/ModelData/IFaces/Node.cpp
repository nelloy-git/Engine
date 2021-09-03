#include "Graphics/ModelData/IFaces/Node.hpp"

#include "Graphics/ModelData/IFaces/Model.hpp"

using namespace Graphics::Draw;

Node::Node(const Model *model,
           int index,
           const glm::mat4 &mat) :
    ModelData(model, index),
    transform(mat){
}

Node::Node(const Model *model,
           int index,
           const glm::vec3 &trans,
           const glm::quat &rot,
           const glm::vec3 &scale) :
    ModelData(model, index),
    transform(trans, rot, scale){
}

Node::~Node(){
}