#pragma once

#include <vector>
#include <unordered_map>

#include "Data/glTF.h"

namespace Graphics {

class ModelData;
class Node;

class Scene {
public:
    Scene(const tinygltf::Model &model,
          const tinygltf::Scene &scene,
          ModelData &data);
    virtual ~Scene();

    void draw();
    void draw() const;

    std::vector<std::shared_ptr<Node>> nodes;

private:
};

}