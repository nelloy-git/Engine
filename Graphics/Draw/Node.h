#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Mesh.h"
#include "Property.hpp"

namespace Graphics::Draw {

class Node {
public:
    struct Pose {
        glm::vec3 translation;
        glm::quat rotation;
        glm::vec3 scale;
    };

public:
    Node(const glm::mat4 &mat);

    Node(const glm::vec3 &translation,
         const glm::quat &rotation,
         const glm::vec3 &scale);

    virtual ~Node();

    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Node> parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;

    const glm::mat4 mat;
    const std::optional<Pose> pose;

private:
    glm::mat4 _getMat(const glm::vec3 &translation,
                      const glm::quat &rotation,
                      const glm::vec3 &scale);

};

}