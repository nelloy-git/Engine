#include "Data/Node.h"

#include "Log.h"

using namespace Graphics;

Node::Node(const tinygltf::Model &model,
           const tinygltf::Node &node,
           const std::unordered_map<int, std::shared_ptr<Node>> &list) :
    _matrix(1.f){
    if (node.matrix.size() != 0){
        if (node.matrix.size() == 16){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    _matrix[i][j] = node.matrix[i * 4 + j];
                }
            }
        } else {
            LOG(WRN) << "wrong matrix size.";
        }
    } else {
        glm::vec3 scale = {node.scale[0], node.scale[1], node.scale[2]};
        glm::quat rot = {node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]};
        glm::vec3 trans = {node.scale[0], node.scale[1], node.scale[2]};

        _matrix = glm::scale(_matrix, scale);
        _matrix = glm::mat4_cast(rot) * _matrix;
        _matrix = glm::translate(_matrix, trans);
    }
    
    for (int i = 0; i < node.children.size(); i++){
        std::shared_ptr<Node> child;
        auto iter = list.find(node.children[i]);

        if (iter == list.end()){
            child = std::make_shared<Node>(model, model.nodes[node.children[i]], list);
        } else {
            child = iter->second;
        }

        children.push_back(child);
    }
}

Node::~Node(){

}