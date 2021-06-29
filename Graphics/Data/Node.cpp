#include "Data/Node.h"

#include "glm/gtc/quaternion.hpp"

#include "Data/ModelData.h"
#include "Log.h"

using namespace Graphics;

Node::Node(const tinygltf::Model &model,
           const tinygltf::Node &node,
           ModelData &data) :
    matrix(1.f){
    _initMatrix(node);
    _initChildren(model, node, data);
    _initMesh(model, node, data);
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
        glm::vec3 scale(1.f);
        if (node.scale.size() == 3){
            scale = {node.scale[0], node.scale[1], node.scale[2]};
        }

        glm::quat rot = {1.f, 0, 0, 0};
        if (node.rotation.size() == 4){
            rot = {
                (float)node.rotation[3], 
                (float)node.rotation[0], 
                (float)node.rotation[1], 
                (float)node.rotation[2]
            };
        }

        glm::vec3 trans(0.f);
        if (node.translation.size() == 3){
            trans = {node.translation[0], node.translation[1], node.translation[2]};
        }

        matrix = glm::scale(matrix, scale);
        matrix = glm::mat4_cast(rot) * matrix;
        matrix = glm::translate(matrix, trans);
    }
}

void Node::_initChildren(const tinygltf::Model &model,
                         const tinygltf::Node &node,
                         ModelData &data){

    for (int i = 0; i < node.children.size(); i++){
        auto node_pos = node.children[i];
        if (node_pos < 0){
            LOG(ERR) << "Wrong child node index " << node_pos;
            continue;
        }

        auto node_iter = data.nodes.find(node_pos);
        if (node_iter == data.nodes.end()){
            data.nodes[node_pos] = std::make_shared<Node>(model, model.nodes[node_pos], data);
            node_iter = data.nodes.find(node_pos);
        }
        children.push_back(node_iter->second);
    }
}

void Node::_initMesh(const tinygltf::Model &model,
                     const tinygltf::Node &node,
                     ModelData &data){
    
    auto mesh_pos = node.mesh;
    if (mesh_pos < 0){
        mesh = nullptr;
        return;
    }

    auto mesh_iter = data.meshes.find(mesh_pos);
    if (mesh_iter == data.meshes.end()){
        data.meshes[mesh_pos] = std::make_shared<Mesh>(model, model.meshes[mesh_pos], data);
        mesh_iter = data.meshes.find(mesh_pos);
    }
    mesh = mesh_iter->second;
}