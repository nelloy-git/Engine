#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    static Program *getActive();

    void use();

    GLuint getAttribLoc(const std::string &name);
    GLuint getAttribLoc(const std::string &name) const;

    bool setUniformVec4f(const std::string &name, const float mat[4]);
    bool setUniformMat4f(const std::string &name, const float mat[16]);

    GLuint id();
    GLuint id() const;

private:
    GLuint _id;
    static Program *_active_program;
};

}