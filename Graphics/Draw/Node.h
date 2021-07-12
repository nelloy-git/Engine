#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Mesh.h"
#include "Property.h"

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

    void draw();
    void draw() const;

    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Node> parent = nullptr;
    std::vector<std::shared_ptr<Node>> children;

    const glm::mat4 init_mat;
    const std::optional<Pose> init_pose;

    Property<glm::mat4, Node> mat;
    /* Has no effect for nodes without init_pose */
    Property<glm::vec3, Node> translation;
    /* Has no effect for nodes without init_pose */
    Property<glm::quat, Node> rotation;
    /* Has no effect for nodes without init_pose */
    Property<glm::vec3, Node> scale;


private:

    bool _mat_changed;
    glm::mat4 _cur_mat;
    glm::mat4 _last_map;
    const glm::mat4 &_getMat();
    void _setMat(const glm::mat4 &mat);

    std::optional<Pose> _cur_pose;

    const glm::vec3 &_getTranslation();
    void _setTranslation(const glm::vec3 &translation);

    const glm::quat &_getRotation();
    void _setRotation(const glm::quat &rotation);

    const glm::vec3 &_getScale();
    void _setScale(const glm::vec3 &scale);

    glm::mat4 _getUpdatedMat(const glm::vec3 &translation,
                             const glm::quat &rotation,
                             const glm::vec3 &scale);

    // void _initMatrix(const tinygltf::Node &node);
};

}