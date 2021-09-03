#include "Graphics/ModelData/GLwrap/TextureGL.hpp"

#include "Graphics/ModelData/GLwrap/TypesGL.h"

using namespace Graphics::Draw;

TextureGL::TextureGL(const Model *model, int index,
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

    _data = std::make_unique<GLwrap::Tex2D>(
        width, height, internal_fmt, pixel_fmt, pixel_type);
        
}

TextureGL::~TextureGL(){
}

void TextureGL::write(const void *ptr, int x, int y, int width, int height){
    _data->write(ptr, x, y, width, height);
}

void TextureGL::enable(int layout){
    _data->enable(layout);
}

TextureWrap TextureGL::getWrapS() const {
    return _wrap_s;
}

void TextureGL::setWrapS(TextureWrap wrap){
    _data->setWrapS(toGLwrap(wrap));
    _wrap_s = wrap;
}

TextureWrap TextureGL::getWrapT() const {
    return _wrap_t;
}

void TextureGL::setWrapT(TextureWrap wrap){
    _data->setWrapT(toGLwrap(wrap));
    _wrap_t = wrap;
}

TextureFilter TextureGL::getMinFilter() const {
    return _min_filter;
}

void TextureGL::setMinFilter(TextureFilter filter){
    _data->setMinFilter(toGLwrap(filter));
    _min_filter = filter;
}

TextureFilter TextureGL::getMagFilter() const {
    return _mag_filter;
}

void TextureGL::setMagFilter(TextureFilter filter){
    _data->setMagFilter(toGLwrap(filter));
    _mag_filter = filter;
}