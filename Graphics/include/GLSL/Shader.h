#pragma once

#include <string>

#include "glad/glad.h"
#include "GLSL/Types.h"

namespace Graphics::GLSL {

class Shader {
public:
    Shader(ShaderType type, const std::string& source);
    virtual ~Shader();

    const GLuint id = 0;

private:
    
};

}