#include "Draw/Object.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace Graphics::Draw;

Object::Object() :
    model(this, &Object::_getModel, &Object::_setModel),
    camera(this, &Object::_getCamera, &Object::_setCamera),
    active_scene(this, &Object::_getActiveScene, &Object::_setActiveScene){
}

Object::~Object(){
}

// const glm::mat4 &Object::getMatrix(const Node &node) const {
//     auto iter = _matrices.find(&node);
//     if (iter == _matrices.end()){
//         return transform.matrix;
//     }
//     return iter->second;
// }

const glm::mat4 &Object::getMatrix(int node_pos) const {
    if (node_pos < 0 || node_pos > _matrices.size()){
        return transform.matrix;
    }
    return _matrices[node_pos];
};

void Object::update(){
    auto mdl = _model;
    if (!mdl){
        return;
    }

    if (_active_scene < 0 && _active_scene >= mdl->scenes.size()){
        return;
    }
    auto scene = mdl->scenes[_active_scene];
    if (!scene){
        return;
    }

    glm::mat4 cam_mat(1.f);
    if (_camera){
        cam_mat = _camera->matrix;
    }

    for (int i = 0; i < _model->nodes.size(); ++i){
        auto node = _model->nodes[i];
        if (!node){
            continue;
        }

        _updateNodeMatrix(*node, cam_mat * transform.matrix);
    }
}

void Object::_updateNodeMatrix(const Node &node, const glm::mat4 &parent_mat){
    auto mat = parent_mat * node.mat;
    _matrices[node.index] = mat;

    for (int i = 0; i < node.children.size(); ++i){
        auto child = node.children[i];
        if (!child){
            continue;
        }
        
        _updateNodeMatrix(*child, mat);
    }
}

const std::shared_ptr<Model> &Object::_getModel(){
    return _model;
}

void Object::_setModel(const std::shared_ptr<Model> &model){
    _matrices.clear();
    _matrices.reserve(model->nodes.size());

    _model = model;
    _need_update = true;

    for (int i = 0; i < model->nodes.size(); ++i){
        auto &node = *model->nodes[i];
        _matrices[node.index] = node.mat;
    }
}

const std::shared_ptr<Camera> &Object::_getCamera(){
    return _camera;
}

void Object::_setCamera(const std::shared_ptr<Camera> &camera){
    _need_update = true;
    _camera = camera;
}

const int &Object::_getActiveScene(){
    static int def = 0;
    if (_active_scene < 0 || (_model && _active_scene > _model->scenes.size())){
        return def;
    }
    return _active_scene;
}

void Object::_setActiveScene(const int &scene){
    _need_update = true;
    _active_scene = scene;
}