#include "Graphics/Utils/Transform.hpp"

using namespace Graphics;

Transform::Transform() :
    _trans(0.f),
    _rot(glm::angleAxis(0.f, glm::vec3(0.f, 0.f, 1.f))),
    _scale(1.f),
    _changed(false),
    mat(1.f){
}

Transform::Transform(const glm::mat4 &mat) :
    _trans(0.f),
    _rot(glm::angleAxis(0.f, glm::vec3(0.f, 0.f, 1.f))),
    _scale(1.f),
    _changed(false),
    mat(mat){
}

Transform::Transform(const glm::vec3 &trans,
                     const glm::quat &rot,
                     const glm::vec3 &scale) :
    _trans(trans),
    _rot(rot),
    _scale(scale),
    _changed(true),
    mat(1.f){
    applyTRS();
}

Transform::Transform(const Transform &other) :
    _trans(other._trans),
    _rot(other._rot),
    _scale(other._scale),
    _changed(other._changed),
    mat(other.mat){
}

Transform::~Transform(){
}

void Transform::applyTRS(){
    if (!_changed){return;}

    auto s = glm::scale(glm::mat4(1.f), _scale);
    auto r = glm::mat4_cast(_rot);
    auto t = glm::translate(glm::mat4(1.f), _trans);
    mat = t * r * s;
    _changed = false;
}