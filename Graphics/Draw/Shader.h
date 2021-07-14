#pragma once

#include <string>
#include <vector>

#include "Draw/Object.h"

namespace Graphics::Draw{

class Shader {
public:
    Shader(){};
    virtual ~Shader(){};

    virtual bool verify() const = 0;
    virtual void draw(const Object &obj) const = 0;
};

}