#pragma once

#include <vector>
#include <memory>

#include "Draw/Primitive.h"

namespace Graphics::Draw {

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    virtual void draw();
    virtual void draw() const;
    
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
};

}