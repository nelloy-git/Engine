#pragma once

#include <string>
#include <vector>

#include "Graphics/Object.hpp"

namespace Graphics::Draw{

class Shader {
public:
    Shader(){};
    virtual ~Shader(){};

    virtual bool verify() = 0;
    virtual void draw(const Object &obj) = 0;
};

}