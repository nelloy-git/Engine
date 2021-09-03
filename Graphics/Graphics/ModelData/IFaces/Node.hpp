#pragma once

#include <optional>
#include <unordered_map>

#include "Graphics/ModelData/IFaces/ModelData.h"
#include "Graphics/ModelData/IFaces/Mesh.hpp"
#include "Graphics/Utils/Transform.hpp"

namespace Graphics::Draw {

class Model;

class Node : public ModelData {
friend Model;

public:
    Node(const Model *model,
         int index,
         const glm::mat4 &mat);

    Node(const Model *model,
         int index,
         const glm::vec3 &translation,
         const glm::quat &rotation,
         const glm::vec3 &scale);

    virtual ~Node();

    Transform transform;
    Mesh *mesh = nullptr;
    Node *parent = nullptr;
    std::vector<Node *> children;

private:
    std::shared_ptr<Node> _parent = nullptr;

    std::vector<int> _children_indices;

};

}