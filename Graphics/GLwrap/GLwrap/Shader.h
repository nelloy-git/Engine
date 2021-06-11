#pragma once

#include <string>

#include "glad/gl.h"

namespace GLwrap {

enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

enum class ComponentSize : GLint {
    Scalar = 1,
    Vec2 = 2,
    Vec3 = 3,
    Vec4 = 4,
    Mat2 = 4,
    Mat3 = 9,
    Mat4 = 16
};

enum class ComponentType : GLenum {
    Byte = GL_BYTE, 
    UByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
};

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