#include "Draw/Object.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Log.h"

using namespace Graphics::Draw;

Object::Object(){
}

Object::~Object(){
}

const Transform &Object::getNodeTransform(const Node &node) const {
    int i = node.index;
    if (i < 0 || i > _node_transforms.size()){
        throw std::invalid_argument("node index is out of range.");
    }
    return _node_transforms[i];
}

void Object::setModel(std::shared_ptr<Model> model){
    _model = model;
    _model_changed = true;
}

std::shared_ptr<Model> Object::getModel() const {
    return _model;
}

void Object::setCamera(std::shared_ptr<Camera> camera){
    _camera = camera;
    _camera_changed = true;
}

std::shared_ptr<Camera> Object::getCamera() const {
    return _camera;
}

void Object::setScene(int index){
    _scene_index = index;
    if (index < 0 || (_model && index > _model->scenes().size())){
        return;
    }
    _scene = _model->scenes()[index];
}

std::shared_ptr<Scene> Object::getScene() const {
    return _scene;
}

void Object::setAnimation(float time, int index){
    _anim_time = time;
    _anim_index = index;
    if (index < 0 || (_model && index > _model->animations().size())){
        return;
    }
    _anim = _model->animations()[index];
}

std::pair<float, int> Object::getAnimation() const {
    return std::make_pair(_anim_time, _anim_index);
}

bool Object::update(){
    if (!_model){return false;}
    if (!_camera){return false;}
    if (!_scene){return false;}

    transform.applyTRS();
    _updateCamera();
    _updateModel();
    _updateScene();
    _updateAnimation();

    if (_node_transforms_changed){
        auto parent_mat = _camera->matrix * transform.mat;
        for (int i = 0; i < _scene->nodes.size(); ++i){
            _updateNodeTransform(*_scene->nodes[i], parent_mat);
        }
    }


    return true;
}

void Object::_updateCamera(){
    if (!_camera_changed){return;}
    _node_transforms_changed = true;
}

void Object::_updateModel(){
    if (!_model_changed){return;}
    _node_transforms_changed = true;

    int s = _model->nodes().size();
    _node_transforms = std::vector<Transform>(s);
    setScene(_scene_index);
}

void Object::_updateScene(){
    if (!_scene_changed){return;}
    _node_transforms_changed = true;
}

void Object::_updateAnimation(){
    if (!_anim_changed){return;}
    _node_transforms_changed = true;
}

void Object::_updateNodeTransform(Node &node, const glm::mat4 &parent_mat){
    Transform *res = &_node_transforms[node.index];
    *res = node.transform;

    if (_anim){
        // for (int i = 0; i < _anim->translations.size(); ++i){
        //     auto ptr = _anim->translations[i];
        //     if (&node == ptr->node.get()){
        //         res->setT(ptr->get(_anim_time, Interpolation::Linear));
        //         break;
        //     }
        // }

        // std::cout << _anim->rotations.size() << std::endl;
        for (int i = 0; i < _anim->rotations.size(); ++i){
            auto ptr = _anim->rotations[i];
            if (&node == ptr->node.get()){
                // std::cout << _anim_time << std::endl;
                res->setR(ptr->get(_anim_time, Interpolation::Linear));
                break;
            }
        }
    }

    res->applyTRS();
    res->mat = parent_mat * res->mat;

    for (int i = 0; i < node.children.size(); ++i){
        auto child = node.children[i];
        if (!child){
            continue;
        }
        
        _updateNodeTransform(*child, res->mat);
    }
}