#include "Draw/Utils/Transform.hpp"

using namespace Graphics::Draw;

Transform::Transform() :
    matrix(this, &Transform::_getMatrix, nullptr),
    translation(this, &Transform::_getTranslation, &Transform::_setTranslation),
    rotation(this, &Transform::_getRotation, &Transform::_setRotation),
    scale(this, &Transform::_getScale, &Transform::_setScale),
    _matrix(1.f),
    _trans(0.f),
    _rot(glm::angleAxis(0.f, glm::vec3(0.f, 0.f, 1.f))),
    _scale(1.f){
}

Transform::~Transform(){
}

const glm::mat4 &Transform::_getMatrix(){
    if (_need_update){
        auto s = glm::scale(glm::mat4(1.f), _scale);
        auto r = glm::mat4_cast(_rot);
        auto t = glm::translate(glm::mat4(1.f), _trans);
        _matrix = t * r * s;
        _need_update = false;
    }

    return _matrix;
};

const glm::vec3 &Transform::_getTranslation(){
    return _trans;
};

void Transform::_setTranslation(const glm::vec3 &translation){
    _trans = translation;
    _need_update = true;
}

const glm::quat &Transform::_getRotation(){
    return _rot;
};

void Transform::_setRotation(const glm::quat &rotation){
    _rot = rotation;
    _need_update = true;
}

const glm::vec3 &Transform::_getScale(){
    return _scale;
};

void Transform::_setScale(const glm::vec3 &scale){
    _scale = scale;
    _need_update = true;
}