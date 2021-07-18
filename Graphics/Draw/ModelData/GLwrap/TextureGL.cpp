#include "Draw/ModelData/GLwrap/TextureGL.hpp"

#include "Draw/ModelData/GLwrap/TypesGL.h"

using namespace Graphics::Draw;

TextureGL::TextureGL(const Model &model, int index,
                     int width, int height, int channels, int bpp) : 
    Texture(model, index, width, height, channels, bpp){

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

TextureGL::~TextureGL(){
}

void TextureGL::write(const void *ptr, int x, int y, int width, int height){
    data->write(ptr, x, y, width, height);
}

void TextureGL::setActive(int layout){
    data->setActive(layout);
}

const TextureWrap &TextureGL::_getWrapS(){
    return _wrap_s;
}

void TextureGL::_setWrapS(const TextureWrap &wrap){
    data->wrap_s = toGLwrap(wrap);
    _wrap_s = wrap;
}

const TextureWrap &TextureGL::_getWrapT(){
    return _wrap_t;
}

void TextureGL::_setWrapT(const TextureWrap &wrap){
    data->wrap_t = toGLwrap(wrap);
    _wrap_t = wrap;
}

const TextureFilter &TextureGL::_getMinFilter(){
    return _min_filter;
}

void TextureGL::_setMinFilter(const TextureFilter &filter){
    data->min_filter = toGLwrap(filter);
    _min_filter = filter;
}

const TextureFilter &TextureGL::_getMagFilter(){
    return _mag_filter;
}

void TextureGL::_setMagFilter(const TextureFilter &filter){
    data->mag_filter = toGLwrap(filter);
    _mag_filter = filter;
}