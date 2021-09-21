#pragma once

#include "Graphics/Render/Base/Vertex.hpp"

namespace Graphics::Model {

class ModelBase;

class Data {
public:
    Data(const ModelBase &model, int index) :
        model(model),
        index(index){
    };
    virtual ~Data(){};

    const ModelBase &model;
    const int index;
};

}