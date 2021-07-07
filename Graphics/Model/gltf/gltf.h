#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Array.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Tex2D.h"

#include "Data/Types.h"

namespace Graphics::Model::gltfConvert {

int getLayoutLocation(const std::string &name);
ComponentSize getComponentSize(int gltf_component_size);
ComponentType getComponentType(int gltf_component_type);
size_t getComponentTypeSize(ComponentType gltf_component_type);
GLwrap::DrawMode getDrawMode(int gltf_draw_mode);

GLwrap::Tex2Dformat getImageFormat(int gltf_channels);
GLuint getImageWrap(int gltf_wrap);
GLuint getImageFilter(int gltf_filter);

}