#pragma once

#include "glad/glad.h"

namespace Graphics::GLSL {

enum class ShaderType : GLenum {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

enum class DataSize : GLint {
    Vec1 = 1,
    Vec2 = 2,
    Vec3 = 3,
    Vec4 = 4,
};

enum class DataType : GLenum {
    Float = GL_FLOAT,
    Byte = GL_BYTE, 
    UByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT
};

}