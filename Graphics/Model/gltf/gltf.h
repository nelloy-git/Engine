#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Array.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Tex2D.h"

#include "Model/Types.h"

namespace Graphics::Model::gltfConvert {

BufferType getBufferType(int type);
BufferElemStruct getBufferElemSize(int gltf_elem_size);
BufferElemType getBufferElemType(int gltf_elem_type);
PrimitiveDrawMode getDrawMode(int gltf_draw_mode);
PrimitiveAttribute getAttribute(const std::string attr);

// size_t getComponentTypeSize(ComponentType gltf_elem_type);
// GLwrap::Tex2Dformat getImageFormat(int gltf_channels);
// GLuint getImageWrap(int gltf_wrap);
// GLuint getImageFilter(int gltf_filter);

}