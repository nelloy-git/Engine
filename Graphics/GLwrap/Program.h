#pragma once

#include <memory>
#include <vector>

#include "glad/gl.h"

#include "GLwrap/Shader.h"

namespace Graphics::GLwrap {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    const GLuint id = 0;

private:
    
};

}