#pragma once

#include "Data/glTF.h"

namespace Graphics {

class Material {
public:
    Material();
    virtual ~Material();

    void apply();

    float base_color[4] = {1, 1, 1, 1};
    std::shared_ptr<GLwrap::Tex2D> base_texture;
    int base_texture_uv = 0;

private:
};

}