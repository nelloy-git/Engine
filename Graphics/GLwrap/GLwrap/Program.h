#pragma once

#include <memory>
#include <vector>

#include "glad/gl.h"

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    GLuint id();

private:
    GLuint __id;
    
};

}