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

    const Model &model;
    const int index;

    const std::vector<std::shared_ptr<Primitive>> &primitives(){
        return _primitives;
    };

    virtual std::shared_ptr<Primitive> addPrimitive() = 0;

protected:
    std::vector<std::shared_ptr<Primitive>> _primitives;
};

}