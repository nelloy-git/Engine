#include "Draw/Object.hpp"

#include "Log.h"

using namespace Graphics::Draw;

Object::Object() :
    _model_mat(transform.mat){
}

Object::~Object(){
}

void Object::update(){
    if (!_model || !_camera || !_scene){
        return;
    }

    transform.applyTRS();
    if (!_changed && _model_mat == transform.mat){
        return;
    }

    _model_mat = transform.mat;
    auto root_mat = _camera->mat * transform.mat;
    for (int i = 0; i <_scene->nodes.size(); ++i){
        _updateNode(*_scene->nodes[i], root_mat);
    }
}

const glm::mat4 *Object::getNodeMat(int index) const {
    if (index < 0 || index >= _node_mats.size()){
        return nullptr;
    }
    return &_node_mats[index];
}

const std::vector<float> *Object::getNodeMorph(int index) const{
    if (index < 0 || index >= _node_weights.size()){
        return nullptr;
    }
    return &_node_weights[index];
}

void Object::setModel(Model *model){
    _changed = _model != model;
    _model = model;
    if (_changed && model){
        int count = model->getNodesCount();
        _node_mats = std::vector<glm::mat4>(count);
        _node_weights = std::vector<std::vector<float>>(count);
    }
    _scene = nullptr;
    _anim = nullptr;
}

Model *Object::getModel() {
    return _model;
}

const Model *Object::getModel() const {
    return _model;
}

void Object::setCamera(Camera *camera){
    _changed = _camera != camera;
    _camera = camera;
}

Camera *Object::getCamera() {
    return _camera;
}

const Camera *Object::getCamera() const {
    return _camera;
}

void Object::setScene(int index){
    if (!_model || index < 0 || index >= _model->getScenesCount()){
        return;
    }

    auto sc = _model->getScene(index);
    _changed = _scene != sc;
    _scene = sc;
}

int Object::getScene() const {
    return _scene ? _scene->index : -1;
}

void Object::setAnimation(int index){
    if (!_model || index < 0 || index >= _model->getAnimationsCount()){
        return;
    }

    auto a = _model->getAnimation(index);
    _changed = _anim != a;
    _anim = a;
    _anim_time = 0;
}

const int Object::getAnimation() const {
    return _anim ? _anim->index : -1;
}

void Object::setAnimationTime(float time){
    if (!_anim){
        return;
    }

    _changed = _anim_time != time;
    _anim_time = time;
}

const float Object::getAnimationTime() const {
    return _anim_time;
}

void Object::_updateNode(const Node &node, const glm::mat4 &root_mat){
    if (node.index < 0 || node.index >= _node_mats.size()){
        return;
    }

    auto mat = &_node_mats[node.index];
    auto morph = &_node_weights[node.index];
    if (_anim){
        // _anim->getMat(node, _anim_time, mat, morph);
        *mat = root_mat * (*mat);
    } else {
        *mat = root_mat * node.transform.mat;
    }

    for (int i = 0; i < node.children.size(); ++i){
        auto child = node.children[i];
        _updateNode(*child, *mat);
    }
}