#pragma once

#include "Data/glTF.h"

namespace Graphics {

class ModelData;

class Material {
public:
    Material(const tinygltf::Model &model,
             const tinygltf::Material &material,
             const ModelData &buffer);
    virtual ~Material();

    void apply();

private:
    std::vector<float> __base_color;
    std::shared_ptr<GLwrap::Tex2D> __base_texture;
    int __base_texture_uv;
};

}