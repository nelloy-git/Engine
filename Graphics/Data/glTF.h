#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Array.h"
#include "GLwrap/Shader.h"

namespace Graphics::glTF {

int getLayoutLocation(const std::string &name);
GLwrap::ComponentSize getComponentSize(int glTF_component_size);
GLwrap::ComponentType getComponentType(int glFT_component_type);
GLwrap::DrawMode getDrawMode(int glTF_draw_mode);

}