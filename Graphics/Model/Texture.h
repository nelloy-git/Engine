#pragma once

#include <memory>

#include "Property.h"

#include "Model/Types.h"

namespace Graphics::Model {

class Texture {
public:
    // void load(const void *data, unsigned int width, unsigned int height,
    //           TextureFormat format, TextureWrap wrap_s, TextureWrap wrap_t, 
    //           TextureFilter min_filter, TextureFilter mag_filter,
    //           unsigned int bits_per_channel);
    virtual void enable(int index) = 0;
    virtual void write(const void *ptr, int x, int y, int width, int height) = 0;

    const int width;
    const int height;
    const int channels;
    const int bpp;

    Property<TextureWrap, Texture> wrap_s;
    Property<TextureWrap, Texture> wrap_t;

    Property<TextureFilter, Texture> min_filter;
    Property<TextureFilter, Texture> mag_filter;

protected:
    Texture(int width, int height, int channels, int bpp) :
        width(width),
        height(height),
        channels(channels),
        bpp(bpp),
        wrap_s(this, &Texture::_getWrapS, &Texture::_setWrapS),
        wrap_t(this, &Texture::_getWrapT, &Texture::_setWrapT),
        min_filter(this, &Texture::_getMinFilter, &Texture::_setMinFilter),
        mag_filter(this, &Texture::_getMagFilter, &Texture::_setMagFilter){
    };
    virtual ~Texture(){};

    virtual const TextureWrap &_getWrapS() = 0;
    virtual void _setWrapS(const TextureWrap &wrap) = 0;

    virtual const TextureWrap &_getWrapT() = 0;
    virtual void _setWrapT(const TextureWrap &wrap) = 0;

    virtual const TextureFilter &_getMinFilter() = 0;
    virtual void _setMinFilter(const TextureFilter &filter) = 0;

    virtual const TextureFilter &_getMagFilter() = 0;
    virtual void _setMagFilter(const TextureFilter &filter) = 0;
};

}