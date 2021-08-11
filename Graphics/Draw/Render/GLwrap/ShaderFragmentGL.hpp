#pragma once

#include <string>

#include "GLwrap/Shader.h"

namespace Graphics::Render {

class ShaderFragmentGL {
public:
    ShaderFragmentGL(const std::string *src = nullptr);
    virtual ~ShaderFragmentGL();

    const GLwrap::Shader gl;

private:
    static const std::string &_getDefaultSrc();

};

}