#pragma once

#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "Data/Primitive.h"

namespace Graphics {

class ModelData;

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