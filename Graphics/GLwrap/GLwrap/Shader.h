#pragma once

#include <string>

#include "Glwrap/Types.h"

namespace GLwrap {

size_t getDataTypeSize(ComponentType type);

class Shader {
public:
    Shader(ShaderType type, const std::string& path);
    virtual ~Shader();

    GLuint id();

private:
    GLuint __id;
    
    std::string __loadFromFile(const std::string &path);
};

}