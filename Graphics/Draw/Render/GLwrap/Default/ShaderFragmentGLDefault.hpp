#pragma once

#include <string>

#include "GLwrap/Shader.h"

#include "Draw/Render/GLwrap/ShaderFragmentGL.hpp"

namespace Graphics::Render {

class ShaderFragmentGLDefault : public ShaderFragmentGL {
public:
    ShaderFragmentGLDefault();
    virtual ~ShaderFragmentGLDefault();

private:
    static const std::string &_getSources();

};

}