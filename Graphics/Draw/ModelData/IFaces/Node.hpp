#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/Mesh.hpp"
#include "Draw/Utils/Transform.hpp"

namespace Graphics::Draw {

class Model;

class Node {
friend Model;

public:
    Node(const Model &model,
         int index,
         const glm::mat4 &mat);
    Node(const Model &model,
         int index,
         const glm::vec3 &translation,
         const glm::quat &rotation,
         const glm::vec3 &scale);

    virtual ~Node();

    const Model &model;
    const int index;

    Transform transform;
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Node> parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;

private:
    std::shared_ptr<Node> _parent = nullptr;

    std::vector<int> _children_indices;

};

}