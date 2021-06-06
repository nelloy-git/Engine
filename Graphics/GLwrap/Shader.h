#pragma once

#include <string>

#include "glad/glad.h"
#include "GLwrap/Types.h"

namespace Graphics::GLwrap {

class Shader {
public:
    Shader(ShaderType type, const std::string& source);
    virtual ~Shader();

    const GLuint id = 0;

private:
    
};

}