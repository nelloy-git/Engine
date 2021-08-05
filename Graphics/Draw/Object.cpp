#include "Draw/Object.hpp"

#include "Log.h"

using namespace Graphics::Draw;

template<typename T>
using Ref = Object::Ref<T>;

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

const std::vector<float> *Object::getNodeMorphWeights(int index) const{
    if (index < 0 || index >= _node_weights.size()){
        return nullptr;
    }
    return &_node_weights[index];
}

void Object::setModel(Ref<Model> model){
    _changed = _model.get() != model.get();
    _model = model;
    if (model){
        _node_mats = std::vector<glm::mat4>(model->nodes().size());
        _node_weights = std::vector<std::vector<float>>(model->nodes().size());
    }
    _scene = nullptr;
    _anim = nullptr;
}

const Ref<Model> Object::getModel() const {
    return _model;
}

void Object::setCamera(Ref<Camera> camera){
    _changed = _camera.get() != camera.get();
    _camera = camera;
}

const Ref<Camera> Object::getCamera() const {
    return _camera;
}

void Object::setScene(int index){
    if (!_model || index < 0 || index >= _model->scenes().size()){
        return;
    }

    auto sc = _model->scenes()[index];
    _changed = _scene.get() != sc.get();
    _scene = sc;
}

const int Object::getScene() const {
    return _scene ? _scene->index : -1;
}

void Object::setAnimation(int index){
    if (!_model || index < 0 || index >= _model->animations().size()){
        return;
    }

    auto a = _model->animations()[index];
    _changed = _anim.get() != a.get();
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

    auto &mat = _node_mats[node.index];
    if (_anim){
        mat = root_mat * _anim->getMat(node, _anim_time);
    } else {
        mat = root_mat * node.transform.mat;
    }

    for (int i = 0; i < node.children.size(); ++i){
        auto child = node.children[i];
        _updateNode(*child, mat);
    }
}