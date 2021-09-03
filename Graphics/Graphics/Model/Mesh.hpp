#pragma once

#include <vector>

#include "Graphics/Render/PrimitiveGL.hpp"

#include "Graphics/Model/Data.hpp"

namespace Graphics::Model {

class Mesh : public Data {
public:
    Mesh(const Model *model, int index) :
        Data(model, index){
    };
    virtual ~Mesh(){};

    std::vector<Render::PrimitiveGL *> primitives;
    std::vector<float> morph;
};

}