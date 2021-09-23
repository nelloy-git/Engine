#pragma once

#include "Graphics/Model/Data.hpp"

#include "Graphics/Model/Texture.hpp"

namespace Graphics::Model {

using Texture = GLwrap::Tex2D;

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    struct TexInfo {
        TexInfo() = default;
        Texture *tex = nullptr;
        unsigned int layer = 0;
        // Multiplicator for pixels
        float scale[4] = {0.0, 0.0, 0.0, 0.0};
    };

    TexInfo color;
    TexInfo pbr;
    TexInfo normal;
    TexInfo occlusion;
    TexInfo emissive;

private:


};

}