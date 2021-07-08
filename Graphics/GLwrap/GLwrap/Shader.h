#pragma once

#include <memory>
#include <string>

#include "GLwrap/Types.h"

namespace GLwrap {

size_t getDataTypeSize(ElementType type);

class Shader {
public:
    Shader(ShaderType type, const std::string& code);
    static std::shared_ptr<Shader> fromFile(ShaderType type, const std::string& path);
    virtual ~Shader();

    GLuint id();

private:
    GLuint __id;
};

}