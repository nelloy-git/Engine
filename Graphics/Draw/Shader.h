#pragma once

#include "Draw/Object.h"

namespace Graphics::Draw{

class Shader {
public:
    Shader();
    virtual ~Shader();

    virtual bool verify() = 0;
    virtual void draw(const Object &obj) = 0;
};

}