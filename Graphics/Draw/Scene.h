#pragma once

#include <vector>
#include <unordered_map>

#include "Draw/Node.h"

namespace Graphics::Draw {

class Scene {
public:
    Scene();
    virtual ~Scene();

    std::vector<std::shared_ptr<Node>> nodes;

protected:
};

}