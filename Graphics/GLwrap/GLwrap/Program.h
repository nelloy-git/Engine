#pragma once

#include <memory>
#include <vector>

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    static Program *getActive();

    void use();

    bool setUniformVec4f(const std::string &name, const float mat[4]);
    bool setUniformMat4f(const std::string &name, const float mat[16]);

    GLuint id();
    GLuint id() const;

private:
    GLuint __id;
    static Program *__active_program;
};

}