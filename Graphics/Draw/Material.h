#pragma once

#include <memory>

#include "Draw/Texture.h"

namespace Graphics::Draw {

class Material {
public:
    Material();
    virtual ~Material();

    void apply();

    float base_color[4] = {1, 1, 1, 1};
    std::shared_ptr<Texture> base_texture;
    int base_texture_uv = 0;

private:
};

}