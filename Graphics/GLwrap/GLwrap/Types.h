#pragma once

#include <string_view>

#include <magic_enum.h>

#include "glad/gl.h"

namespace GLwrap {

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
    Array = GL_ARRAY_BUFFER,
    IndexArray = GL_ELEMENT_ARRAY_BUFFER,
};

enum class BufferUsage : GLenum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
};

enum class ElementStruct : GLint {
    Scalar = 1,
    Vec2 = 2,
    Vec3 = 3,
    Vec4 = 4,
    Mat2 = 4,
    Mat3 = 9,
    Mat4 = 16
};

enum class ElementType : GLenum {
    Byte = GL_BYTE, 
    UByte = GL_UNSIGNED_BYTE,
    Short = GL_SHORT,
    UShort = GL_UNSIGNED_SHORT,
    Int = GL_INT,
    UInt = GL_UNSIGNED_INT,
    Float = GL_FLOAT,
    Double = GL_DOUBLE,
};

template<ElementType E>
struct toType {
    using type = typename std::conditional_t<E == ElementType::Byte, char,
                          std::conditional_t<E == ElementType::UByte, unsigned char, 
                          std::conditional_t<E == ElementType::Short, short int, 
                          std::conditional_t<E == ElementType::UShort, unsigned short int, 
                          std::conditional_t<E == ElementType::Int, int, 
                          std::conditional_t<E == ElementType::UInt, unsigned int, 
                          std::conditional_t<E == ElementType::Float, float, 
                          double>>>>>>>;
};

template<typename T>
constexpr ElementType fromType(){
    static_assert(std::is_same_v<T, char>
                  || std::is_same_v<T, unsigned char>
                  || std::is_same_v<T, short int>
                  || std::is_same_v<T, unsigned short int>
                  || std::is_same_v<T, int>
                  || std::is_same_v<T, unsigned int>
                  || std::is_same_v<T, float>
                  || std::is_same_v<T, double>,
                    "Is not ElementType");

    if (std::is_same_v<T, char>){
        return ElementType::Byte;

    } else if (std::is_same_v<T, unsigned char>){
        return ElementType::UByte;

    } else if (std::is_same_v<T, short int>){
        return ElementType::Short;

    } else if (std::is_same_v<T, unsigned short int>){
        return ElementType::UShort;

    } else if (std::is_same_v<T, int>){
        return ElementType::Int;

    } else if (std::is_same_v<T, unsigned int>){
        return ElementType::UInt;

    } else if (std::is_same_v<T, float>){
        return ElementType::Float;

    } else if (std::is_same_v<T, double>){
        return ElementType::Double;
    }
}

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
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,

    ALPHA = GL_ALPHA,
    ALPHA4 = GL_ALPHA4,
    ALPHA8 = GL_ALPHA8,
    ALPHA12 = GL_ALPHA12,
    ALPHA16 = GL_ALPHA16,
    COMPRESSED_ALPHA = GL_COMPRESSED_ALPHA,
    COMPRESSED_LUMINANCE = GL_COMPRESSED_LUMINANCE,
    COMPRESSED_LUMINANCE_ALPHA = GL_COMPRESSED_LUMINANCE_ALPHA,
    COMPRESSED_INTENSITY = GL_COMPRESSED_INTENSITY,
    COMPRESSED_RGB = GL_COMPRESSED_RGB,
    COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
    DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
    DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
    LUMINANCE = GL_LUMINANCE,
    LUMINANCE4 = GL_LUMINANCE4,
    LUMINANCE8 = GL_LUMINANCE8,
    LUMINANCE12 = GL_LUMINANCE12,
    LUMINANCE16 = GL_LUMINANCE16,
    LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
    LUMINANCE4_ALPHA4 = GL_LUMINANCE4_ALPHA4,
    LUMINANCE6_ALPHA2 = GL_LUMINANCE6_ALPHA2,
    LUMINANCE8_ALPHA8 = GL_LUMINANCE8_ALPHA8,
    LUMINANCE12_ALPHA4 = GL_LUMINANCE12_ALPHA4,
    LUMINANCE12_ALPHA12 = GL_LUMINANCE12_ALPHA12,
    LUMINANCE16_ALPHA16 = GL_LUMINANCE16_ALPHA16,
    INTENSITY = GL_INTENSITY,
    INTENSITY4 = GL_INTENSITY4,
    INTENSITY8 = GL_INTENSITY8,
    INTENSITY12 = GL_INTENSITY12,
    INTENSITY16 = GL_INTENSITY16,
    R3_G3_B2 = GL_R3_G3_B2,
    RGB4 = GL_RGB4,
    RGB5 = GL_RGB5,
    RGB8 = GL_RGB8,
    RGB10 = GL_RGB10,
    RGB12 = GL_RGB12,
    RGB16 = GL_RGB16,
    RGBA2 = GL_RGBA2,
    RGBA4 = GL_RGBA4,
    RGB5_A1 = GL_RGB5_A1,
    RGBA8 = GL_RGBA8,
    RGB10_A2 = GL_RGB10_A2,
    RGBA12 = GL_RGBA12,
    RGBA16 = GL_RGBA16,
    SLUMINANCE = GL_SLUMINANCE,
    SLUMINANCE8 = GL_SLUMINANCE8,
    SLUMINANCE_ALPHA = GL_SLUMINANCE_ALPHA,
    SLUMINANCE8_ALPHA8 = GL_SLUMINANCE8_ALPHA8,
    SRGB = GL_SRGB,
    SRGB8 = GL_SRGB8,
    SRGB_ALPHA = GL_SRGB_ALPHA,
    SRGB8_ALPHA8 = GL_SRGB8_ALPHA8
};

enum class Tex2DPixelFormat : GLenum {
    COLOR_INDEX = GL_COLOR_INDEX,
    RED = GL_RED,
    GREEN = GL_GREEN,
    BLUE = GL_BLUE,
    ALPHA = GL_ALPHA,
    RG = GL_RG,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    LUMINANCE = GL_LUMINANCE,
    LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA
};

enum class Tex2DPixelType : GLenum {
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    BYTE = GL_BYTE,
    BITMAP = GL_BITMAP,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    SHORT = GL_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    INT = GL_INT,
    FLOAT = GL_FLOAT,
    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
};

template<typename T>
std::string toString(T enum_value){
    static_assert(std::is_enum_v<T> && std::is_same_v<T, std::decay_t<T>>, "Enum type is required.");

    constexpr auto type_name = magic_enum::enum_type_name<T>();
    auto enum_name = magic_enum::enum_name(enum_value);
    return std::string(type_name) + std::string("::") + std::string(enum_name);
}

}