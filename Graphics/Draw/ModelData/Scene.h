#pragma once

#include <vector>
#include <unordered_map>

#include "Draw/Node.h"

namespace Graphics::Draw {

class Scene {
public:
    std::vector<std::shared_ptr<Node>> nodes;

protected:
    Scene();
    virtual ~Scene() = 0;
};

Scene::~Scene(){}

}