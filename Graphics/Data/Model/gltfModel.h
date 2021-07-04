#pragma once

#include "Data/Model.h"

namespace tinygltf {
class Model;
class Primitive;
}

namespace Graphics {

class gltfModel : public Model {
public:
    gltfModel(const std::string &path);
    ~gltfModel() override;

private:
    tinygltf::Model *_loadGltfModel(const std::string &path);
    std::shared_ptr<Primitive> _loadPrimitive(const tinygltf::Primitive &gltf_prim);
    std::shared_ptr<Material> _loadMaterial(const tinygltf::Material &gltf_material);
    std::shared_ptr<GLwrap::Tex2D> _loadTexture(const tinygltf::Texture &gltf_texture,
                                                const tinygltf::Model &model);
};

}