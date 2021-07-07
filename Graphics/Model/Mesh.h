#pragma once

#include <vector>
#include <memory>

#include "Model/Primitive.h"

namespace Graphics::Model {

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    void draw();
    void draw() const;
    
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
};

}