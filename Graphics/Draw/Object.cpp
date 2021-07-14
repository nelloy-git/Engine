#include "Draw/Object.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace Graphics::Draw;

Object::Object() :
    matrix(this, &Object::_getMatrix, nullptr),
    translation(this, &Object::_getTranslation, Object::_setTranslation),
    rotation(this, &Object::_getRotation, Object::_setRotation),
    scale(this, &Object::_getScale, Object::_setScale),
    model(this, &Object::_getModel, &Object::_setModel),
    _default_mat(1.f){
}

Object::~Object(){
}

const glm::mat4 &Object::getMatrix(const Node &node){
    auto iter = _matrices.find(node);
    if (iter == _matrices.end()){
        return _default_mat;
    }
    return iter->second;
}

const glm::mat4 &Object::_getMatrix(){
    if (_matrix_need_update){
        auto s = glm::scale(glm::mat4(1.f), _scale);
        auto r = glm::mat4_cast(_rot);
        auto t = glm::translate(glm::mat4(1.f), _trans);
        _matrix = t * r * s;
        _matrix_need_update = false;
    }

    return _matrix;
};

const glm::vec3 &Object::_getTranslation(){
    return _trans;
};

void Object::_setTranslation(const glm::vec3 &translation){
    _trans = translation;
    _matrix_need_update = true;
}

const glm::quat &Object::_getRotation(){
    return _rot;
};

void Object::_setRotation(const glm::quat &rotation){
    _rot = rotation;
    _matrix_need_update = true;
}

const glm::vec3 &Object::_getScale(){
    return _scale;
};

void Object::_setScale(const glm::vec3 &scale){
    _scale = scale;
    _matrix_need_update = true;
}

const std::shared_ptr<Model> &Object::_getModel(){
    return _model;
}

void Object::_setModel(const std::shared_ptr<Model> &model){
    _matrices.clear();
    _model = model;

    for (int i = 0; i < model->nodes.size(); ++i){
        auto &node = *model->nodes[i];
        _matrices[node] = node.mat;
    }
}