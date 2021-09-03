#pragma once

#include <vector>

#include "Graphics/Model/Data.hpp"
#include "Graphics/Utils/Transform.hpp"

namespace Graphics::Model {

class Mesh;

class Node : public Data {
public:
    Node(const Model *model, int index, const glm::mat4 &mat) :
        Data(model, index),
        transform(mat){
    };

    Node(const Model *model, int index,
         const glm::vec3 &translation, const glm::quat &rotation, const glm::vec3 &scale) :
        Data(model, index),
        transform(translation, rotation, scale){
    };

    virtual ~Node(){};

    Transform transform;
    Mesh *mesh = nullptr;
    Node *parent = nullptr;
    std::vector<Node *> children;
};

}