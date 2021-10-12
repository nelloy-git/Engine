#pragma once

#include <string_view>

#include "glad/gl.h"

namespace glw {

enum class gpu_data_type : GLenum {
    GLbyte = GL_BYTE, 
    GLubyte = GL_UNSIGNED_BYTE,
    GLshort = GL_SHORT,
    GLushort = GL_UNSIGNED_SHORT,
    GLint = GL_INT,
    GLuint = GL_UNSIGNED_INT,
    GLfloat = GL_FLOAT,
    GLdouble = GL_DOUBLE,
    GLuint_2_10_10_10 = GL_UNSIGNED_INT_2_10_10_10_REV,
    GLint_2_10_10_10 = GL_INT_2_10_10_10_REV,
    GLuint_10_11_11 = GL_UNSIGNED_INT_10F_11F_11F_REV
};

enum class DrawMode : GLenum {
    Points = GL_POINTS,
    Line = GL_LINE,
    LineLoop = GL_LINE_LOOP,
    LineStrip = GL_LINE_STRIP,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan = GL_TRIANGLE_FAN
};

enum class ShaderType : GLenum {
    Vertex = GL_VERTEX_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

enum class BufferType : GLenum {
    Data = GL_ARRAY_BUFFER,
    Index = GL_ELEMENT_ARRAY_BUFFER
};

enum class BufferUsage : GLenum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
};

enum class DataSize : GLint {
    Scalar = 1,
    Vec2 = 2,
    Vec3 = 3,
    Vec4 = 4,
    Mat3 = 9,
    Mat4 = 16
};

enum class Tex2DWrap : GLint {
    Repeat = GL_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    MirroredRepeat = GL_MIRRORED_REPEAT
};

enum class Tex2DFilter : GLint {
    Linear = GL_LINEAR,
    LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
    LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
    Nearest = GL_NEAREST,
    NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST
};

enum class Tex2DInternalFormat : GLenum {
    Depth = GL_DEPTH_COMPONENT,
    DepthStencil = GL_DEPTH_STENCIL,
    Red = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
};

enum class Tex2DPixelDataFormat : GLenum {
    Red = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,

    RedInt = GL_RED_INTEGER,
    RGInt = GL_RG_INTEGER,
    RGBInt = GL_RGB_INTEGER,
    BGRInt = GL_BGR_INTEGER,
    RGBAInt = GL_RGBA_INTEGER,
    BGRAInt = GL_BGRA_INTEGER,

    StencilIndex = GL_STENCIL_INDEX,
    DepthComponent = GL_DEPTH_COMPONENT,
    DepthStencil = GL_DEPTH_STENCIL
};

enum class Tex2DPixelDataType : GLenum { 
    GLubyte = GL_UNSIGNED_BYTE,
    GLbyte = GL_BYTE,
    GLushort = GL_UNSIGNED_SHORT,
    GLshort = GL_SHORT,
    GLuint = GL_UNSIGNED_INT,
    GLint = GL_INT,
    GLhfloat = GL_HALF_FLOAT,
    GLfloat = GL_FLOAT,
    
    GLubyte_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    GLubyte_2_3_3 = GL_UNSIGNED_BYTE_2_3_3_REV,
    GLushort_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    GLushort_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    GLushort_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    GLushort_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    GLushort_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    GLushort_5_5_5_1_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    GLuint_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    GLuint_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    GLuint_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    GLuint_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

}