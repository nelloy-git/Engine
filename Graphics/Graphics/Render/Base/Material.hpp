#pragma once

#include "Graphics/Model/Data.hpp"

#include "Graphics/Model/Texture.hpp"

namespace Graphics::Render::Base {

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    struct TexInfo {
        TexInfo() = default;
        GLwrap::Tex2D *tex = nullptr;
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