#pragma once

#include <vector>
#include <utility>

#include "glad/gl.h"

namespace GLwrap {

enum class Tex2DParamInt : GLenum {
    WRAP_S = GL_TEXTURE_WRAP_S,
    WRAP_T = GL_TEXTURE_WRAP_T,
    MIN_FILTER = GL_TEXTURE_MIN_FILTER,
    MAG_FILTER = GL_TEXTURE_MAG_FILTER,
};

enum class Tex2DinternalFormat : GLenum {
    CHANNELS_1 = 1,
    CHANNELS_2 = 2,
    CHANNELS_3 = 3,
    CHANNELS_4 = 4,

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
    RGB = GL_RGB,
    RGB4 = GL_RGB4,
    RGB5 = GL_RGB5,
    RGB8 = GL_RGB8,
    RGB10 = GL_RGB10,
    RGB12 = GL_RGB12,
    RGB16 = GL_RGB16,
    RGBA = GL_RGBA,
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

enum class Tex2Dformat : GLenum {
    COLOR_INDEX = GL_COLOR_INDEX,
    RED = GL_RED,
    GREEN = GL_GREEN,
    BLUE = GL_BLUE,
    ALPHA = GL_ALPHA,
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    LUMINANCE = GL_LUMINANCE,
    LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA
};

enum class Tex2DpixelType {
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

class Tex2D {
public:
    Tex2D();
    ~Tex2D();

    void free();

    void bind();
    void unbind();

    void setActive(GLuint index);

    void load(const void *data, GLsizei width, GLsizei height, 
              Tex2DinternalFormat in_fmt = Tex2DinternalFormat::RGBA,
              Tex2Dformat usage = Tex2Dformat::RGBA,
              Tex2DpixelType pixel = Tex2DpixelType::UNSIGNED_BYTE,
              const std::vector<std::pair<Tex2DParamInt, GLuint>> &uint_params = Tex2D::__default_uint_params);

    GLuint id();

private:

    GLuint __id;
    bool __loaded = false;
    GLsizei __loaded_width = 0;
    GLsizei __loaded_height = 0;

    static const std::vector<std::pair<Tex2DParamInt, GLuint>> __default_uint_params;
};

}