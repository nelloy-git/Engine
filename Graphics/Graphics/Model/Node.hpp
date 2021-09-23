#pragma once

#include <vector>

#include "Graphics/Utils/Transform.hpp"

#include "Graphics/Model/Mesh.hpp"

namespace Graphics::Model {

template<Render::Base::VertexStruct S>
class Node {
public:
    explicit Node(const glm::mat4 &mat) noexcept :
        transform(mat){
    };

    explicit Node(const glm::vec3 &translation,
                  const glm::quat &rotation,
                  const glm::vec3 &scale) noexcept :
        transform(translation, rotation, scale){
    };
    Node(const Node&) = delete;
    Node(Node &&) = default;
    virtual ~Node() = default;

    Transform transform;
    Mesh<S> *mesh = nullptr;
    Node *parent = nullptr;
    std::vector<Node *> children;
};

}