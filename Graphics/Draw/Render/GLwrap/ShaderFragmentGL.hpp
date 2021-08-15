#pragma once

#include <string>

#include "GLwrap/Shader.h"

namespace Graphics::Render {

class ShaderFragmentGL {
public:
    ShaderFragmentGL(const std::string &src) :
        gl(GLwrap::ShaderType::Fragment, src){
    };
    virtual ~ShaderFragmentGL(){};

    const GLwrap::Shader gl;
};

}