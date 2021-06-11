#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Array.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Tex2D.h"

namespace Graphics::glTF {

int getLayoutLocation(const std::string &name);
GLwrap::ComponentSize getComponentSize(int glTF_component_size);
GLwrap::ComponentType getComponentType(int glFT_component_type);
GLwrap::DrawMode getDrawMode(int glTF_draw_mode);

GLwrap::Tex2Dformat getImageFormat(int glTF_channels);
GLuint getImageWrap(int glTF_wrap);
GLuint getImageFilter(int glTF_filter);

}