#include "Drawing/Drawer.h"

#include <algorithm>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Log.h"

using namespace Graphics;

Drawer *Drawer::_gl_active = nullptr;

Drawer::Drawer(glm::vec2 pos, glm::vec2 size){
    _pos = pos;
    _size = size;
}

Drawer::~Drawer(){
}

bool Drawer::isActive(){
    return _active;
}

bool Drawer::setActive(bool f){
    if (_camera == nullptr || _shader == nullptr){
        return false;
    }

    _active = true;
    Drawer::_gl_active = this;

    glViewport((int)_pos.x, (int)_pos.y, (int)_size.x, (int)_size.y);
    _shader->use();
    return true;
}

std::shared_ptr<Camera> Drawer::camera(){
    return _camera;
}

void Drawer::setCamera(std::shared_ptr<Camera> camera){
    _camera = camera;
}

std::shared_ptr<GLwrap::Program> Drawer::shader(){
    return _shader;
}

void Drawer::setShader(std::shared_ptr<GLwrap::Program> shader){
    // TODO shader verify

    _shader = shader;
}

bool Drawer::clear(const glm::vec4 &color){
    if (!_active){
        return false;
    }
    
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    return true;
}

bool Drawer::draw(const Model::Model &model,
                  const glm::vec3 &translation,
                  const glm::quat &rotation,
                  const glm::vec3 &scale){
    if (!_active || _camera == nullptr || _shader == nullptr){
        return false;
    }

    auto cam_mat = _camera->matrix();

    auto scaled = glm::scale(glm::mat4(1.f), scale);
    auto rotated = glm::mat4_cast(rotation) * scaled;
    const glm::mat4 model_mat = cam_mat * glm::translate(rotated, translation);

    if (!_shader->setUniformMat4f("model", glm::value_ptr(model_mat))){
        LOG(ERR) << "\"model\" not found.";
    };

    for (auto mesh : model.meshes){
        mesh->draw();
    }
    
    // model.scenes[0]->draw();

    // model.nodes[0]->translation = translate;
    // model.nodes[0]->rotation = rotate;
    // model.nodes[0]->scale = scale;

    // for (int i = 0; i < model.nodes.size(); i++){
    //     const glm::mat4 &mat = model.nodes[i]->mat;

    //     auto node_mat = model_mat * mat;
    //     if (!_shader->setUniformMat4f("model", glm::value_ptr(node_mat))){
    //         LOG(ERR) << "\"model\" not found.";
    //     };

    //     model.nodes[i]->draw();
    // }


    // for (auto node : model.nodes){
    //     node->draw();
    // }

    return true;
}

bool Drawer::draw(const Model::Primitive &primitive, const glm::mat4 &pos){
    if (!_active || _camera == nullptr || _shader == nullptr){
        return false;
    }

    auto cam_mat = _camera->matrix();

    glm::mat4 model_mat = cam_mat * pos;
    
    if (!_shader->setUniformMat4f("model", glm::value_ptr(model_mat))){
        LOG(ERR) << "\"model\" not found.";
    };
    primitive.draw();
    return true;
}