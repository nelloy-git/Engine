#pragma once

#include <memory>
#include <string>
#include <vector>

#include "assimp/scene.h"

#include "Data/Mesh.h"
#include "Data/Texture.h"

namespace Graphics::Data {

struct ModelTexture {

};

class Model {
public:
    Model();
    virtual ~Model();

    bool load(const std::string &path);

    const std::vector<std::shared_ptr<Mesh>> &meshes(){return __meshes;};
    const std::vector<std::shared_ptr<Texture>> &textures(){return __textures;};

private:
    bool __loadMeshes(const aiScene &scene);
    bool __loadTextures(const aiScene &scene);

    std::string __path;

    std::vector<std::shared_ptr<Mesh>> __meshes;
    std::vector<std::shared_ptr<Texture>> __textures;
};

}
