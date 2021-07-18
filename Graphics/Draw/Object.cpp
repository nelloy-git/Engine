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

void Object::update(){
    auto mdl = _model;
    if (!mdl){
        return;
    }

    if (_active_scene < 0 && _active_scene >= mdl->scenes().size()){
        return;
    }

    auto scene = mdl->scenes()[active_scene];
    if (!scene){
        return;
    }

    glm::mat4 cam_mat(1.f);
    if (_camera){
        cam_mat = _camera->matrix;
    }

    _matrices.clear();
    _matrices.reserve(mdl->nodes().size());

    for (int i = 0; i < scene->nodes.size(); ++i){
        _updateNodeMatrix(*scene->nodes[i], cam_mat * transform.matrix);
    }
}

bool Object::changed(){
    return _need_update;
}

const glm::mat4 &Object::getMatrix(const Node &node) const {
    if (node.index < 0 || node.index > _matrices.max_size()){
        return transform.matrix;
    }
    return _matrices[node.index];
};

void Object::_updateNodeMatrix(const Node &node, const glm::mat4 &parent_mat){
    _matrices[node.index] = parent_mat * node.transform.matrix;

    for (int i = 0; i < node.children.size(); ++i){
        auto child = node.children[i];
        if (!child){
            continue;
        }
        
        _updateNodeMatrix(*child, _matrices[node.index]);
    }
}

const std::shared_ptr<Model> &Object::_getModel(){
    return _model;
}

void Object::_setModel(const std::shared_ptr<Model> &model){
    _need_update = _model.get() != model.get();
    _model = model;
}

const std::shared_ptr<Camera> &Object::_getCamera(){
    return _camera;
}

void Object::_setCamera(const std::shared_ptr<Camera> &camera){
    _need_update = _camera.get() != camera.get();
    _camera = camera;
}

const int &Object::_getActiveScene(){
    static int def = 0;
    if (_active_scene < 0 || (_model && _active_scene > _model->scenes().size())){
        return def;
    }
    return _active_scene;
}

void Object::_setActiveScene(const int &scene){
    _need_update = _active_scene != scene;
    _active_scene = scene;
}