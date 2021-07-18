#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Draw/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class Model;

class Material {
public:
    Material(const Model &model, int index) :
        model(model),
        index(index){};
    virtual ~Material(){};

    const Model &model;
    int index;

    glm::vec4 base_color = {1.f, 1.f, 1.f, 1.f};
    std::shared_ptr<Texture> base_texture = nullptr;
};

}