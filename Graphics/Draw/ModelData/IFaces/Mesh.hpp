#pragma once

#include <vector>
#include <memory>

#include "Draw/ModelData/IFaces/Primitive.hpp"

namespace Graphics::Draw {

class Mesh {
public:
    Mesh(const Model &model, int index) :
        model(model),
        index(index){};
    virtual ~Mesh(){};

    const std::vector<std::shared_ptr<Primitive>> &primitives(){
        return _primitives;
    };

    virtual std::shared_ptr<Primitive> addPrimitive() = 0;

    const Model &model;
    const int index;
    std::vector<float> morph;

protected:
    std::vector<std::shared_ptr<Primitive>> _primitives;
};

}