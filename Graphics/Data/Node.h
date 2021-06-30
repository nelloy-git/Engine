#pragma once

#include <unordered_map>

#include "glm/glm.hpp"

#include "Data/glTF.h"

namespace Graphics {

class Mesh;
class ModelData;

class Node {
public:
    Node(const tinygltf::Node &node,
         ModelData &data);
    virtual ~Node();

    void draw();
    void draw() const;

    std::shared_ptr<Mesh> mesh;
    std::vector<std::shared_ptr<Node>> children;
    glm::mat4 matrix;

private:
    void _initMatrix(const tinygltf::Node &node);
};

}