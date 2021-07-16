#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Mesh.h"
#include "Draw/Utils/Transform.hpp"
#include "Property.hpp"

namespace Graphics::Draw {

class Node {
public:
    Transform transform;
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Node> parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;

private:
    Node(const glm::mat4 &mat);
    Node(const glm::vec3 &translation,
         const glm::quat &rotation,
         const glm::vec3 &scale);

    virtual ~Node() = 0;
};

Node::~Node(){}

}