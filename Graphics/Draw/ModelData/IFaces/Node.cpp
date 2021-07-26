#include "Draw/ModelData/IFaces/Node.hpp"

#include "Draw/ModelData/IFaces/Model.hpp"

using namespace Graphics::Draw;

Node::Node(const Model &model,
           int index,
           const glm::mat4 &mat) :
    index(index),
    model(model),
    transform(mat){
}

Node::Node(const Model &model,
           int index,
           const glm::vec3 &trans,
           const glm::quat &rot,
           const glm::vec3 &scale) :
    index(index),
    model(model),
    transform(trans, rot, scale){
}

Node::~Node(){
}