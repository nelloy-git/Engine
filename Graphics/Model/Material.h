#pragma once

#include <memory>

#include "Model/Texture.h"

namespace Graphics::Model {

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    void apply();

    float base_color[4] = {1, 1, 1, 1};
    std::shared_ptr<Texture> base_texture;
    int base_texture_uv = 0;

private:
};

}