#pragma once

#include <string>

#include "glad/glad.h"

namespace Graphics::GLSL {

class Shader {
public:
    Shader(const std::string& source);
    virtual ~Shader();

    const GLuint id = 0;

private:
    
};

}