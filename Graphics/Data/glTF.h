#pragma once

#include <string>

#include "tiny_gltf.h"

#include "GLwrap/Vao.h"
#include "GLwrap/Shader.h"

namespace Graphics::glTF {

int getAttrLoc(const std::string &name);
GLwrap::ShaderDataSize getAttrComponentSize(int glTF_component_size);
GLwrap::ShaderDataType getAttrComponentType(int glFT_component_type);
GLwrap::VAOdrawMode getDrawMode(int glTF_draw_mode);

}