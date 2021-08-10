#pragma once

#include <vector>
#include <unordered_map>

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

class Scene : public ModelData {
public:
    Scene(const Model *model, int index) :
        ModelData(model, index){};
    virtual ~Scene(){};

    std::vector<Node *> nodes;
};

}