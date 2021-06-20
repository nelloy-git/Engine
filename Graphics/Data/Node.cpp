#include "Data/Node.h"

#include "glm/gtc/quaternion.hpp"

#include "Data/ModelData.h"
#include "Log.h"

using namespace Graphics;

Node::Node(const tinygltf::Model &model,
           const tinygltf::Node &node,
           const ModelData &data) :
    matrix(1.f){
    // _initMatrix(node);

    if (node.mesh >= 0){
        mesh = data.meshes()[node.mesh];
    }
}

Node::~Node(){

}

void Node::draw(){
    if (mesh){
        mesh->draw();
    }

    for (auto &child : children){
        child->draw();
    }
}

void Node::draw() const{
    if (mesh){
        mesh->draw();
    }

    for (auto &child : children){
        child->draw();
    }
}

void Node::_initMatrix(const tinygltf::Node &node){
    if (node.matrix.size() != 0){
        if (node.matrix.size() == 16){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    matrix[i][j] = node.matrix[i * 4 + j];
                }
            }
        } else {
            LOG(WRN) << "wrong matrix size.";
        }
    } else {
        glm::vec3 scale = {node.scale[0], node.scale[1], node.scale[2]};
        glm::quat rot = {
            (float)node.rotation[3], 
            (float)node.rotation[0], 
            (float)node.rotation[1], 
            (float)node.rotation[2]
        };
        glm::vec3 trans = {node.scale[0], node.scale[1], node.scale[2]};

        matrix = glm::scale(matrix, scale);
        matrix = glm::mat4_cast(rot) * matrix;
        matrix = glm::translate(matrix, trans);
    }
}