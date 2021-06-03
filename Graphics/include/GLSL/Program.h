#pragma once

#include <memory>
#include <vector>

#include "glad/glad.h"

#include "GLSL/Shader.h"

namespace Graphics::GLSL {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>>& attach);
    virtual ~Program();

    

    const GLuint id = 0;

private:
    
};

}