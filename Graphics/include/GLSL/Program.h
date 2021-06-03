#pragma once

#include <vector>

#include "glad/glad.h"

#include "GLSL/Shader.h"

namespace Graphics::GLSL {

class Program {
public:
    Program(std::vector<Shader*>& attach);
    virtual ~Program();

    

    const GLuint id = 0;

private:
    
};

}