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
           const glm::vec3 &translation,
           const glm::quat &rotation,
           const glm::vec3 &scale) :
    index(index),
    model(model),
    transform(){
    
    transform.translation = translation;
    transform.rotation = rotation;
    transform.scale = scale;
}

Node::~Node(){
}