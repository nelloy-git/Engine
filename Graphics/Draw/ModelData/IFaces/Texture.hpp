#pragma once

#include "Draw/Types.h"

#include "Draw/ModelData/IFaces/ModelData.h"

namespace Graphics::Draw {

class Texture : public ModelData {
public:
    Texture(const Model *model, int index, int width, int height, int channels, int bpp) :
        ModelData(model, index),
        width(width),
        height(height),
        channels(channels),
        bpp(bpp){
    };
    virtual ~Texture(){};

    virtual void write(const void *ptr, int x, int y, int width, int height) = 0;

    virtual TextureWrap getWrapS() const = 0;
    virtual void setWrapS(TextureWrap wrap) = 0;

    virtual TextureWrap getWrapT() const = 0;
    virtual void setWrapT(TextureWrap wrap) = 0;

    virtual TextureFilter getMinFilter() const = 0;
    virtual void setMinFilter(TextureFilter filter) = 0;

    virtual TextureFilter getMagFilter() const = 0;
    virtual void setMagFilter(TextureFilter filter) = 0;

    const int width;
    const int height;
    const int channels;
    const int bpp;

protected:
};

}