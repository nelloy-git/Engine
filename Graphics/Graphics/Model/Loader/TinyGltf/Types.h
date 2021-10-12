#pragma once

#include <stdexcept>
#include <string>
#include <experimental/source_location>

#include "tiny_gltf.h"

#include "Graphics/Types.h"
#include "GLwrap/Types.h"

namespace Graphics::Model::gltf {

namespace detailed {
    
using SrcLoc = std::experimental::source_location;

[[ noreturn ]] static inline void throwErr(const std::string &msg, SrcLoc loc = SrcLoc::current()){
    throw std::runtime_error(std::string(loc.file_name()) + ":"
                             + std::to_string(loc.line()) + " - "
                             + msg);
}

}

GLwrap::DrawMode getDrawMode(const tinygltf::Primitive &prim);
GLwrap::Type getElemType(const tinygltf::Accessor &acc);
GLwrap::Size getElemStruct(const tinygltf::Accessor &acc);

GLwrap::Tex2DFilter getMinFilter(const tinygltf::Sampler &sampler);
GLwrap::Tex2DFilter getMagFilter(const tinygltf::Sampler &sampler);
GLwrap::Tex2DWrap getWrapT(const tinygltf::Sampler &sampler);
GLwrap::Tex2DWrap getWrapS(const tinygltf::Sampler &sampler);

GLwrap::Tex2DInternalFormat getInternalFormat(const tinygltf::Image& img);
GLwrap::Tex2DPixelFormat getPixelFormat(const tinygltf::Image& img);
GLwrap::Tex2DPixelType getPixelType(const tinygltf::Image& img);

}