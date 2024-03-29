#pragma once

#include "GLwrap/Tex2D.h"

#include "Graphics/Model/Data.hpp"

namespace tinygltf {
    class Image;
    class Model;
    class Texture;
}

namespace Graphics::Model {

class Texture : public Data, public glw::Tex2D {
public:
    Texture(const ModelBase &model, int index,
            const tinygltf::Model &gltf_model, const tinygltf::Texture &gltf_texture);
    virtual ~Texture();

private:
    static const tinygltf::Image &_getImg(const tinygltf::Model &gltf_model,
                                          const tinygltf::Texture &gltf_texture);
    static glw::Tex2DInternalFormat _getInternalFmt(const tinygltf::Image &gltf_image);
    static glw::Tex2DPixelDataFormat _getPixelFmt(const tinygltf::Image &gltf_image);
    static glw::Tex2DPixelType _getPixelType(const tinygltf::Image &gltf_image);
};

}