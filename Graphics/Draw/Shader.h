#pragma once

#include <string>
#include <vector>

#include "Draw/Object.hpp"

namespace Graphics::Draw{

class Shader {
public:
    Shader(){};
    virtual ~Shader(){};

    virtual bool verify() = 0;
    virtual void draw(const Object &obj, const glm::mat4 &camera_mat) = 0;
};

}