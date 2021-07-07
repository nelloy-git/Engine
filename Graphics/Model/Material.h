#pragma once

#include <memory>

namespace GLwrap {
    class Tex2D;
}

namespace Graphics {

class Material {
public:
    Material() = default;
    virtual ~Material() = default;

    void apply();

    float base_color[4] = {1, 1, 1, 1};
    std::shared_ptr<GLwrap::Tex2D> base_texture;
    int base_texture_uv = 0;

private:
};

}