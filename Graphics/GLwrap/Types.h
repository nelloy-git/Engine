#pragma once

#include <stdexcept>

#include "glad/gl.h"

namespace Graphics::GLwrap {

enum class BufferType : GLenum {
    ARRAY = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
};

enum class UsageType : GLenum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
};

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

enum class Tex2DParamInt : GLenum {
    WRAP_S = GL_TEXTURE_WRAP_S,
    WRAP_T = GL_TEXTURE_WRAP_T,
    MIN_FILTER = GL_TEXTURE_MIN_FILTER,
    MAG_FILTER = GL_TEXTURE_MAG_FILTER,
};

size_t getShaderDataTypeSize(ShaderDataType type);

}