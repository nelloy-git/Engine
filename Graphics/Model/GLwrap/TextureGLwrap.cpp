#include "Model/GLwrap/TextureGLwrap.h"

#include "Model/GLwrap/TypesGLwrap.h"

#include "Log.h"

using namespace Graphics::Model;

TextureGLwrap::TextureGLwrap(int width, int height, int channels, int bpp) : 
    Texture(width, height, channels, bpp){

    GLwrap::Tex2DInternalFormat internal_fmt;
    GLwrap::Tex2DPixelFormat pixel_fmt;
    switch (channels){
        case 1:
            internal_fmt = GLwrap::Tex2DInternalFormat::RED;
            pixel_fmt = GLwrap::Tex2DPixelFormat::RED;
            break;
        case 2:
            internal_fmt = GLwrap::Tex2DInternalFormat::RG;
            pixel_fmt = GLwrap::Tex2DPixelFormat::RG;
            break;
        case 3:
            internal_fmt = GLwrap::Tex2DInternalFormat::RGB;
            pixel_fmt = GLwrap::Tex2DPixelFormat::RGB;
            break;
        default:
            internal_fmt = GLwrap::Tex2DInternalFormat::RGBA;
            pixel_fmt = GLwrap::Tex2DPixelFormat::RGBA;
    }


    auto pixel_type = bpp == 8 ? GLwrap::Tex2DPixelType::UNSIGNED_BYTE
                               : GLwrap::Tex2DPixelType::UNSIGNED_SHORT;

    data = std::make_shared<GLwrap::Tex2D>(
        width, height, internal_fmt, pixel_fmt, pixel_type);
        
}

TextureGLwrap::~TextureGLwrap(){
}

void TextureGLwrap::enable(int index){
    data->setActive(index);
}

void TextureGLwrap::write(const void *ptr, int x, int y, int width, int height){
    data->write(ptr, x, y, width, height);
}

const TextureWrap &TextureGLwrap::_getWrapS(){
    return _wrap_s;
}

void TextureGLwrap::_setWrapS(const TextureWrap &wrap){
    data->wrap_s = toGLwrap(wrap);
    _wrap_s = wrap;
}

const TextureWrap &TextureGLwrap::_getWrapT(){
    return _wrap_t;
}

void TextureGLwrap::_setWrapT(const TextureWrap &wrap){
    data->wrap_t = toGLwrap(wrap);
    _wrap_t = wrap;
}

const TextureFilter &TextureGLwrap::_getMinFilter(){
    return _min_filter;
}

void TextureGLwrap::_setMinFilter(const TextureFilter &filter){
    data->min_filter = toGLwrap(filter);
    _min_filter = filter;
}

const TextureFilter &TextureGLwrap::_getMagFilter(){
    return _mag_filter;
}

void TextureGLwrap::_setMagFilter(const TextureFilter &filter){
    data->mag_filter = toGLwrap(filter);
    _mag_filter = filter;
}