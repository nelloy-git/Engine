#pragma once

#include <unordered_map>

#include "glm/gtc/quaternion.hpp"

#include "Data/glTF.h"
#include "Data/ModelBuffer.h"

namespace Graphics {

class Node {
public:
    Node(const tinygltf::Model &model,
         const tinygltf::Node &node,
         const std::unordered_map<int, std::shared_ptr<Node>> &list);
    virtual ~Node();

    std::shared_ptr<Mesh> mesh;
    std::vector<std::shared_ptr<Node>> children;

private:
    glm::mat4 _matrix;
};

}