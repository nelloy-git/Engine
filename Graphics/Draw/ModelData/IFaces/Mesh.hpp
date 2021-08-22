#pragma once

#include <vector>
#include <memory>

#include "Draw/Render/GLwrap/PrimitiveGL.hpp"

#include "Draw/ModelData/IFaces/ModelData.h"
#include "Draw/ModelData/IFaces/Primitive.hpp"

namespace Graphics::Draw {

class Mesh : public ModelData, std::vector<std::unique_ptr<Primitive>> {
friend class ModelLoader;

public:
    Mesh(const Model *model, int index) :
        ModelData(model, index){};
    virtual ~Mesh(){};

    std::vector<float> morph;
};

}