#pragma once

#include <memory>

#include "GLwrap/Shader.h"

#include "Draw/Render/PrimitiveGL.hpp"

namespace Graphics::Render {

class FragmentShaderGL {
public:
    explicit FragmentShaderGL(const std::string &source = FragmentShaderGL::_getSource());
    virtual ~FragmentShaderGL();

    std::unique_ptr<GLwrap::Shader> gl;

private:
    static const std::string &_getSource();
};

}