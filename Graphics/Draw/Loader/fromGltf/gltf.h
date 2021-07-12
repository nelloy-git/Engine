#pragma once

#include <string>

#include "tiny_gltf.h"

#include "Draw/Types.h"

namespace Graphics::Draw::gltfConvert {

BufferType getBufferType(int type);
BufferElemStruct getBufferElemStruct(int gltf_elem_size);
BufferElemType getBufferElemType(int gltf_elem_type);
PrimitiveDrawMode getDrawMode(int gltf_draw_mode);
PrimitiveAttribute getAttribute(const std::string &gltf_attr);
TextureFilter getTextureFilter(int gltf_filter);
TextureWrap getTextureWrap(int gltf_wrap);
TextureFormat getTextureFormat(int gltf_channels);

// size_t getComponentTypeSize(ComponentType gltf_elem_type);
// GLwrap::Tex2Dformat getImageFormat(int gltf_channels);
// GLuint getImageWrap(int gltf_wrap);
// GLuint getImageFilter(int gltf_filter);

}