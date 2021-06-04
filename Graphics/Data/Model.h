#pragma once

#include <memory>
#include <string>
#include <vector>

#include "assimp/scene.h"

#include "VBO/Array.h"

#include "Data/Mesh.h"

namespace Graphics::Data {

class Model {
public:
    Model();
    virtual ~Model();

    bool load(const std::string &path);
    // bool draw();
    std::vector<std::shared_ptr<Mesh>> meshes;

private:
    bool __loadMeshes(const aiScene &scene);
};

}
