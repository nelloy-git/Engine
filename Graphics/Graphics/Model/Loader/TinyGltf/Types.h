#pragma once

#include <string>

#include "Graphics/Types.h"
#include "GLwrap/Types.h"

namespace Graphics::Model::gltf {

GLwrap::BufferType toBufferType(int type);
GLwrap::DrawMode toDrawMode(int mode);
GLwrap::ElementType toElemType(int elem_type);
GLwrap::ElementStruct toElemStruct(int elem_struct);

GLwrap::Tex2DFilter toTextureFilter(int filter);
GLwrap::Tex2DWrap toTextureWrap(int wrap);

// BufferElemStruct getBufferElemStruct(int gltf_elem_size);
// PrimitiveDrawMode getDrawMode(int gltf_draw_mode);
// PrimitiveAttribute getAttribute(const std::string &gltf_attr);
// TextureFormat getTextureFormat(int gltf_channels);

// size_t getComponentTypeSize(ComponentType gltf_elem_type);
// GLwrap::Tex2Dformat getImageFormat(int gltf_channels);
// GLuint getImageWrap(int gltf_wrap);
// GLuint getImageFilter(int gltf_filter);

}