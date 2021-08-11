#pragma once

#include <string>

#include "GLwrap/Shader.h"

namespace Graphics::Render {

class ShaderVertexGL {
public:
    ShaderVertexGL(const std::string *src = nullptr);
    virtual ~ShaderVertexGL();

    const GLwrap::Shader gl;

private:
    static const std::string &_getDefaultSrc();

};

}