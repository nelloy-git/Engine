#pragma once

#include <memory>

#include "GLwrap/Shader.h"

#include "Draw/Render/PrimitiveGL.hpp"

namespace Graphics::Render {

class VertexShaderGL {
public:
    explicit VertexShaderGL(const std::string &source = VertexShaderGL::_getSource());
    virtual ~VertexShaderGL();

    std::unique_ptr<GLwrap::Shader> gl;

private:
    static const std::string &_getSource();
};

}