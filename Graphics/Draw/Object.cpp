#include "Draw/Object.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace Graphics::Draw;

Object::Object() :
    model(this, &Object::_getModel, &Object::_setModel){
}

Object::~Object(){
}

const glm::mat4 &Object::getMatrix(const Node &node) const {
    auto iter = _matrices.find(&node);
    if (iter == _matrices.end()){
        return transform.matrix;
    }
    return iter->second;
}

void Object::update(){
    auto mdl = model.get();
    if (!mdl){
        return;
    }

    for (int i = 0; i < mdl->scenes.size(); ++i){
        auto scene = mdl->scenes[i];
        if (!scene){
            continue;
        }

        for (int j = 0; j < scene->nodes.size(); ++j){
            auto node = scene->nodes[i];
            if (!node){
                continue;
            }

            _updateNodeMatrix(*node);
        }
    }
}

void Object::_updateNodeMatrix(const Node &node){
    auto &parent_mat = getMatrix(*node.parent);
    _matrices[&node] = parent_mat * node.mat;

    for (int i = 0; i < node.children.size(); ++i){
        _updateNodeMatrix(*node.children[i]);
    }
}

const std::shared_ptr<Model> &Object::_getModel(){
    return _model;
}

void Object::_setModel(const std::shared_ptr<Model> &model){
    _matrices.clear();
    _model = model;

    for (int i = 0; i < model->nodes.size(); ++i){
        auto &node = *model->nodes[i];
        _matrices[&node] = node.mat;
    }
}