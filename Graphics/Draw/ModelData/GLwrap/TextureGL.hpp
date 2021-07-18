#pragma once

#include "GLwrap/Tex2D.h"

#include "Draw/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class TextureGL : public Texture {
public:
    TextureGL(const Model &model, int index, int width, int height, int channels, int bpp);
    virtual ~TextureGL();

    void write(const void *ptr, int x, int y, int width, int height);

    void setActive(int layout);

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