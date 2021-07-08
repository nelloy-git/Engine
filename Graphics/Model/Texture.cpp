#include "Model/Texture.h"

#include <unordered_map>

#include "GLwrap/Tex2D.h"

using namespace Graphics::Model;

constexpr inline GLwrap::Tex2Dformat toGL(TextureFormat fmt){
    constexpr GLwrap::Tex2Dformat map[] = {
        GLwrap::Tex2Dformat::RED,
        GLwrap::Tex2Dformat::RG,
        GLwrap::Tex2Dformat::RGB,
        GLwrap::Tex2Dformat::RGBA,
    };

    return map[toUint(fmt)];
}

constexpr inline GLuint toGL(TextureWrap wrap){
    constexpr GLuint map[] = {
        GL_REPEAT,
        GL_CLAMP_TO_EDGE,
        GL_MIRRORED_REPEAT
    };

    return map[toUint(wrap)];
}

constexpr inline GLuint toGL(TextureFilter filter){
    constexpr GLuint map[] = {
        GL_LINEAR,
        GL_LINEAR_MIPMAP_LINEAR,
        GL_LINEAR_MIPMAP_NEAREST,
        GL_NEAREST,
        GL_NEAREST_MIPMAP_LINEAR,
        GL_NEAREST_MIPMAP_NEAREST,
    };

    return map[toUint(filter)];
}

Texture::Texture() : 
    width(this, &Texture::_getWidth), 
    height(this, &Texture::_getHeight),
    wrap_s(this, &Texture::_getWrapS),
    wrap_t(this, &Texture::_getWrapT),
    min_filter(this, &Texture::_getMinFilter),
    mag_filter(this, &Texture::_getMagFilter){
}

Texture::~Texture(){
}

void Texture::load(const void *data, unsigned int width, unsigned int height,
                   TextureFormat format, TextureWrap wrap_s, TextureWrap wrap_t, 
                   TextureFilter min_filter, TextureFilter mag_filter,
                   unsigned int bits_per_channel){

    std::vector<std::pair<GLwrap::Tex2DParamInt, GLuint>> sampler_params = {
        {GLwrap::Tex2DParamInt::WRAP_S, toGL(wrap_s)},
        {GLwrap::Tex2DParamInt::WRAP_T, toGL(wrap_t)},
        {GLwrap::Tex2DParamInt::MIN_FILTER, toGL(min_filter)},
        {GLwrap::Tex2DParamInt::MAG_FILTER, toGL(mag_filter)},
    };

    texture = std::make_shared<GLwrap::Tex2D>();
    texture->load(data, width, height,
                  GLwrap::Tex2DinternalFormat::RGBA,
                  toGL(format),
                  bits_per_channel == 8 ? GLwrap::Tex2DpixelType::UNSIGNED_BYTE : GLwrap::Tex2DpixelType::UNSIGNED_SHORT,
                  sampler_params);
    
    _width = width;
    _height = height;
    _wrap_s = wrap_s;
    _wrap_t = wrap_t;
    _min_filter = min_filter;
    _mag_filter = mag_filter;
}

const unsigned int &Texture::_getWidth(){
    return _width;
}

const unsigned int &Texture::_getHeight(){
    return _height;
}

const TextureWrap &Texture::_getWrapS(){
    return _wrap_s;
}

const TextureWrap &Texture::_getWrapT(){
    return _wrap_t;
}

const TextureFilter &Texture::_getMinFilter(){
    return _min_filter;
}

const TextureFilter &Texture::_getMagFilter(){
    return _mag_filter;
}
