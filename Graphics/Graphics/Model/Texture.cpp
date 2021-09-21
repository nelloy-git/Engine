#include "Graphics/Model/Texture.hpp"

#include "tiny_gltf.h"

// #include "Graphics/Model/Loader/TinyGltf"

using namespace Graphics::Model;

Texture::Texture(const ModelBase &model, int index,
                 const tinygltf::Model &gltf_model, const tinygltf::Texture &gltf_texture) :
    Data(model, index),
    GLwrap::Tex2D(_getImg(gltf_model, gltf_texture).width,
                  _getImg(gltf_model, gltf_texture).height,
                  _getInternalFmt(_getImg(gltf_model, gltf_texture)),
                  _getPixelFmt(_getImg(gltf_model, gltf_texture)),
                  _getPixelType(_getImg(gltf_model, gltf_texture))){
    // auto &img = gltf_model.images[gltf_texture.source];
    // write(img.image.data(), 0, 0, img.width, img.height);

    // if (gltf_texture.sampler >= 0){
    //     auto &sampler = gltf_model.samplers[gltf_texture.sampler];

    //     auto wrap_s = gltf::toTextureWrap(sampler.wrapS);
    //     if (wrap_s != GLwrap::Tex2DWrap::Unknown){
    //         setWrapS(wrap_s);
    //     }

    //     auto wrap_t = gltf::toTextureWrap(sampler.wrapT);
    //     if (wrap_t != GLwrap::Tex2DWrap::Unknown){
    //         setWrapT(wrap_t);
    //     }

    //     auto filter_min = gltf::toTextureFilter(sampler.minFilter);
    //     if (filter_min != GLwrap::Tex2DFilter::Unknown){
    //         setMinFilter(filter_min);
    //     }

    //     auto filter_mag = gltf::toTextureFilter(sampler.magFilter);
    //     if (filter_mag != GLwrap::Tex2DFilter::Unknown){
    //         setMagFilter(filter_mag);
    //     }
    // }
}

Texture::~Texture(){
    
}

const tinygltf::Image &Texture::_getImg(const tinygltf::Model &gltf_model,
                                  const tinygltf::Texture &gltf_texture){
    return gltf_model.images[gltf_texture.source];
}

GLwrap::Tex2DInternalFormat Texture::_getInternalFmt(const tinygltf::Image &gltf_image){
    switch (gltf_image.component){
        case 1:
            return GLwrap::Tex2DInternalFormat::RED;
        case 2:
            return GLwrap::Tex2DInternalFormat::RG;
        case 3:
            return GLwrap::Tex2DInternalFormat::RGB;
        default:
            return GLwrap::Tex2DInternalFormat::RGBA;
    }
}

GLwrap::Tex2DPixelFormat Texture::_getPixelFmt(const tinygltf::Image &gltf_image){
    switch (gltf_image.component){
        case 1:
            return GLwrap::Tex2DPixelFormat::RED;
        case 2:
            return GLwrap::Tex2DPixelFormat::RG;
        case 3:
            return GLwrap::Tex2DPixelFormat::RGB;
        default:
            return GLwrap::Tex2DPixelFormat::RGBA;
    }
}

GLwrap::Tex2DPixelType Texture::_getPixelType(const tinygltf::Image &gltf_image){
    return gltf_image.bits == 8 ? GLwrap::Tex2DPixelType::UNSIGNED_BYTE
                                : GLwrap::Tex2DPixelType::UNSIGNED_SHORT;
}
