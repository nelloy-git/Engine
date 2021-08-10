#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class Model;

class Material : public ModelData {
public:
    Material(const Model *model, int index) :
        ModelData(model, index){};
    virtual ~Material(){};

    glm::vec4 base_color = {1.f, 1.f, 1.f, 1.f};
    Texture *base_texture = nullptr;
};

}