#pragma once

#include <memory>

#include "GLwrap/Tex2D.h"

#include "Graphics/ModelData/IFaces/Texture.hpp"

namespace Graphics::Draw {

class TextureGL : public Texture {
public:
    TextureGL(const Model *model, int index, int width, int height, int channels, int bpp);
    virtual ~TextureGL();

    void write(const void *ptr, int x, int y, int width, int height);
    void enable(int layout);

    virtual void setWrapS(TextureWrap wrap) override;
    virtual TextureWrap getWrapS() const override;

    virtual void setWrapT(TextureWrap wrap) override;
    virtual TextureWrap getWrapT() const override;

    virtual void setMinFilter(TextureFilter filter) override;
    virtual TextureFilter getMinFilter() const override;

    virtual void setMagFilter(TextureFilter filter) override;
    virtual TextureFilter getMagFilter() const override;

    GLwrap::Tex2D *getData();

private:
    TextureWrap _wrap_s;
    TextureWrap _wrap_t;

    TextureFilter _min_filter;
    TextureFilter _mag_filter;

    std::unique_ptr<GLwrap::Tex2D> _data;
};

}