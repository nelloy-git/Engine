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

    void use();
    GLuint getUniformLoc(const std::string &name);

    void setUniformMat4f(const std::string &name, const float mat[16]);

    GLuint id();

private:
    GLuint __id;
    
};

}