#pragma once

#include <memory>

#include "Property.h"

#include "Model/Types.h"

namespace GLwrap {
    class Tex2D;
}

namespace Graphics::Model {

class Texture {
public:
    Texture();
    virtual ~Texture();

    void load(const void *data, unsigned int width, unsigned int height,
              TextureFormat format, TextureWrap wrap_s, TextureWrap wrap_t, 
              TextureFilter min_filter, TextureFilter mag_filter,
              unsigned int bits_per_channel);

    const Property<unsigned int, Texture> width;
    const Property<unsigned int, Texture> height;

    const Property<TextureWrap, Texture> wrap_s;
    const Property<TextureWrap, Texture> wrap_t;

    const Property<TextureFilter, Texture> min_filter;
    const Property<TextureFilter, Texture> mag_filter;

    std::shared_ptr<GLwrap::Tex2D> texture;

private:

    unsigned int _width;
    const unsigned int &_getWidth();

    unsigned int _height;
    const unsigned int &_getHeight();

    TextureWrap _wrap_s;
    const TextureWrap &_getWrapS();

    TextureWrap _wrap_t;
    const TextureWrap &_getWrapT();

    TextureFilter _min_filter;
    const TextureFilter &_getMinFilter();

    TextureFilter _mag_filter;
    const TextureFilter &_getMagFilter();
};

}