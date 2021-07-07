#pragma once

#include <vector>
#include <memory>

#include "Model/Primitive.h"

namespace Graphics::Model {

class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    void draw(const GLwrap::Program &prog);
    void draw(const GLwrap::Program &prog) const;
    
    std::vector<std::shared_ptr<Primitive>> primitives;

private:
};

}