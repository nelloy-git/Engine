#pragma once

#include <memory>
#include <string>
#include <vector>

#include "tiny_gltf.h"

#include "Data/Mesh_glTF.h"

namespace Graphics::Data {

class Model_glTF {
public:
    Model_glTF();
    virtual ~Model_glTF();

    void draw();
    bool load(const std::string &path);

    // const std::vector<std::shared_ptr<Mesh>> &meshes(){return __meshes;};
    // const std::vector<std::shared_ptr<Texture>> &textures(){return __textures;};

private:

    void __loadNode(const tinygltf::Model &model,
                    const tinygltf::Node &node);

    std::vector<std::shared_ptr<Mesh_glTF>> __meshes;

    // bool __loadMeshes(const aiScene &scene);
    // bool __loadTextures(const aiScene &scene);

    // std::string __path;

    // std::vector<std::shared_ptr<Mesh>> __meshes;
    // std::vector<std::shared_ptr<Texture>> __textures;
};

}
