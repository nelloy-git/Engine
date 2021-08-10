#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:
    Program(const std::vector<const Shader *> &attach);
    virtual ~Program();

    void use() const;

    GLuint getAttribLoc(const std::string &name);
    GLuint getUniformLoc(const std::string &name);

    bool setUniform1vi(const std::string &name, const int val);
    bool setUniform1vf(const std::string &name, const float val);
    bool setUniformVec4f(const std::string &name, const float vec[4]);
    bool setUniformMat4f(const std::string &name, const float mat[16]);

    bool setUniformFloatArray(const std::string &name, const float *ptr, size_t size);

    const GLuint id;

private:
    std::unordered_map<std::string, GLint> _attributes;
    std::unordered_map<std::string, GLint> _uniforms;
};

}