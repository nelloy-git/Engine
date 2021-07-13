#include "Draw/Node.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Log.h"

using namespace Graphics::Draw;

Node::Node(const glm::mat4 &mat) :
    mat(mat){
}

Node::Node(const glm::vec3 &translation,
           const glm::quat &rotation,
           const glm::vec3 &scale) : 
    pose({translation, rotation, scale}),
    mat(_getMat(translation, rotation, scale)){

}

Node::~Node(){
}

glm::mat4 Node::_getMat(const glm::vec3 &translation,
                               const glm::quat &rotation,
                               const glm::vec3 &scale){

    auto s = glm::scale(glm::mat4(1.f), scale);
    auto r = glm::mat4_cast(rotation);
    auto t = glm::translate(glm::mat4(1.f), translation);
    return t * r * s;
}