#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Draw/Texture.h"

namespace Graphics::Draw {

class Material {
public:
    glm::vec4 base_color = {1.f, 1.f, 1.f, 1.f};
    std::shared_ptr<Texture> base_texture = nullptr;

protected:
    Material();
    virtual ~Material() = 0;
};

Material::~Material(){}

}