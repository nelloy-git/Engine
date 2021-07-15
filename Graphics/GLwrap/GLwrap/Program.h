#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:
    Program(const std::vector<std::shared_ptr<Shader>> &attach);
    virtual ~Program();

    void use() const;

    GLuint getAttribLoc(const std::string &name);
    GLuint getUniformLoc(const std::string &name);

    bool setUniformVec4f(const std::string &name, const float mat[4]);
    bool setUniformMat4f(const std::string &name, const float mat[16]);

    const GLuint id;

private:
    std::unordered_map<std::string, GLint> _attributes;
    std::unordered_map<std::string, GLint> _uniforms;
};

}