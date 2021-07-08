#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Array.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Tex2D.h"

#include "Data/Types.h"

namespace Graphics::glTF {

int getLayoutLocation(const std::string &name);
ComponentSize getComponentSize(int glTF_component_size);
ComponentType getComponentType(int glFT_component_type);
size_t getComponentTypeSize(ComponentType type);
GLwrap::DrawMode getDrawMode(int glTF_draw_mode);

GLwrap::Tex2DPixelFormat getImageFormat(int glTF_channels);
GLwrap::Tex2DWrap getImageWrap(int glTF_wrap);
GLuint getImageFilter(int glTF_filter);

}