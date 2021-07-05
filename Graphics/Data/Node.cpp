#include "Data/Node.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Log.h"

using namespace Graphics;

Node::Node(const glm::mat4 &mat) :
    init_mat(mat),
    mat(this, &Node::_getMat),
    translation(this, &Node::_getTranslation, &Node::_setTranslation),
    rotation(this, &Node::_getRotation, &Node::_setRotation),
    scale(this, &Node::_getScale, &Node::_setScale),
    _mat_changed(false),
    _cur_mat(mat){


}

Node::Node(const glm::vec3 &translation,
           const glm::quat &rotation,
           const glm::vec3 &scale) : 
    init_mat(_getUpdatedMat(translation, rotation, scale)),
    init_pose({translation, rotation, scale}),
    mat(this, &Node::_getMat),
    translation(this, &Node::_getTranslation, &Node::_setTranslation),
    rotation(this, &Node::_getRotation, &Node::_setRotation),
    scale(this, &Node::_getScale, &Node::_setScale),
    _mat_changed(true),
    _cur_mat(_getUpdatedMat(translation, rotation, scale)),
    _cur_pose({translation, rotation, scale}){

}

Node::~Node(){

}

void Node::draw(){
    if (mesh){
        mesh->draw();
    }
}

void Node::draw() const{
    if (mesh){
        mesh->draw();
    }
}

const glm::mat4 &Node::_getMat(){
    glm::mat4 parent_mat = parent ? parent->mat : glm::mat4(1.f);

    if (!_mat_changed || !_cur_pose){
        _last_map = parent_mat * _cur_mat;
        return _last_map;
    }

    Pose &pose = _cur_pose.value();
    _cur_mat = _getUpdatedMat(pose.translation, pose.rotation, pose.scale);
    _mat_changed = false;

    _last_map = parent_mat * _cur_mat;
    return _last_map;
}

const glm::vec3 &Node::_getTranslation(){
    static const glm::vec3 def(0, 0, 0);
    return _cur_pose ? _cur_pose.value().translation : def;
}

void Node::_setTranslation(const glm::vec3 &translation){
    if (!_cur_pose){return;}

    _cur_pose.value().translation = translation;
    _mat_changed = true;
}

const glm::quat &Node::_getRotation(){
    static const glm::quat def(0, 0, 0, 0);
    return _cur_pose ? _cur_pose.value().rotation : def;
}

void Node::_setRotation(const glm::quat &rotation){
    if (!_cur_pose){return;}

    _cur_pose.value().rotation = rotation;
    _mat_changed = true;
}

const glm::vec3 &Node::_getScale(){
    static const glm::vec3 def(0, 0, 0);
    return _cur_pose ? _cur_pose.value().scale : def;
}

void Node::_setScale(const glm::vec3 &scale){
    if (!_cur_pose){return;}

    _cur_pose.value().scale = scale;
    _mat_changed = true;
}

glm::mat4 Node::_getUpdatedMat(const glm::vec3 &translation,
                               const glm::quat &rotation,
                               const glm::vec3 &scale){

    auto s = glm::scale(glm::mat4(1.f), scale);
    auto r = glm::mat4_cast(rotation);
    auto t = glm::translate(glm::mat4(1.f), translation);
    return t * r * s;
}

// void Node::_initMatrix(const tinygltf::Node &node){    
//     if (node.matrix.size() != 0){
//         if (node.matrix.size() == 16){
//             for (int i = 0; i < 4; i++){
//                 for (int j = 0; j < 4; j++){
//                     matrix[i][j] = node.matrix[i * 4 + j];
//                 }
//             }
//         } else {
//             LOG(WRN) << "wrong matrix size.";
//         }
//     } else {
//         glm::vec3 scale(1.f);
//         if (node.scale.size() == 3){
//             scale = {node.scale[0], node.scale[1], node.scale[2]};
//         }

//         glm::quat rot = {1.f, 0, 0, 0};
//         if (node.rotation.size() == 4){
//             rot = {
//                 (float)node.rotation[3], 
//                 (float)node.rotation[0], 
//                 (float)node.rotation[1], 
//                 (float)node.rotation[2]
//             };
//         }

//         glm::vec3 trans(0.f);
//         if (node.translation.size() == 3){
//             trans = {node.translation[0], node.translation[1], node.translation[2]};
//         }

//         matrix = glm::scale(matrix, scale);
//         matrix = glm::mat4_cast(rot) * matrix;
//         matrix = glm::translate(matrix, trans);
//     }
// }