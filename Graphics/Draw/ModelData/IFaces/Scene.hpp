#pragma once

#include <vector>
#include <unordered_map>

#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class Scene {
public:
    Scene(const Model &mode, int index) :
        model(model),
        index(index){};
    virtual ~Scene(){};

    const Model &model;
    const int index;

    std::vector<std::shared_ptr<Node>> nodes;
};

}