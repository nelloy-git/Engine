#pragma once

#include <string>

#include "glad/gl.h"

namespace GLwrap {

enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

enum class ShaderDataSize : GLint {
    Vec1 = 1,
    Vec2 = 2,
    Vec3 = 3,
    Vec4 = 4,
};

enum class ShaderDataType : GLenum {
    Float = GL_FLOAT,
    Byte = GL_BYTE, 
    UByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT
};

class Shader {
public:
    Shader(ShaderType type, const std::string& path);
    virtual ~Shader();

    static size_t getDataTypeSize(ShaderDataType type);

    GLuint id();

private:
    GLuint __id;
    
    std::string __loadFromFile(const std::string &path);
};

}