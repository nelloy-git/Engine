#pragma once

#include "GLwrap/Tex2D.h"

#include "Model/Texture.h"

namespace Graphics::Model {

class TextureGLwrap : public Texture {
public:
    TextureGLwrap(int width, int height, int channels, int bpp);
    virtual ~TextureGLwrap();

    void enable(int index) override;
    void write(const void *ptr, int x, int y, int width, int height);

    std::shared_ptr<GLwrap::Tex2D> data;

private:
    TextureWrap _wrap_s;
    const TextureWrap &_getWrapS() override;
    void _setWrapS(const TextureWrap &wrap) override;

    TextureWrap _wrap_t;
    const TextureWrap &_getWrapT() override;
    void _setWrapT(const TextureWrap &wrap) override;

    TextureFilter _min_filter;
    const TextureFilter &_getMinFilter() override;
    void _setMinFilter(const TextureFilter &filter) override;

    TextureFilter _mag_filter;
    const TextureFilter &_getMagFilter() override;
    void _setMagFilter(const TextureFilter &filter) override;
};

}