#pragma once

#include <vector>
#include <memory>

#include "Draw/Primitive.h"

namespace Graphics::Draw {

class Mesh {
public:
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
    Mesh(){};
    virtual ~Mesh() = 0;
};

Mesh::~Mesh(){}

}