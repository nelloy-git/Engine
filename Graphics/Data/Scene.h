#pragma once

#include <vector>

#include "Data/glTF.h"
#include "Data/ModelData.h"
#include "Data/Node.h"

namespace Graphics {

class Scene {
public:
    Scene(const tinygltf::Model &model,
          const tinygltf::Scene &scene,
          const ModelData &buffer);
    virtual ~Scene();

private:
    std::vector<std::shared_ptr<Node>> _nodes;
};

}