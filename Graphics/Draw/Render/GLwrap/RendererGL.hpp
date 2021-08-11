#pragma once

#include <memory>

#include "GLwrap/Program.h"

#include "Draw/Render/Renderer.hpp"
#include "Draw/Render/GLwrap/ShaderInputGL.hpp"
#include "Draw/Render/GLwrap/ShaderVertexGL.hpp"
#include "Draw/Render/GLwrap/ShaderFragmentGL.hpp"

namespace Graphics::Render {

class RendererGL : public Renderer {
public:
    RendererGL(const std::string *input = nullptr,
               const std::string *vertex = nullptr,
               const std::string *fragment = nullptr);
    virtual ~RendererGL();

protected:
    std::unique_ptr<ShaderInputGL> _input_shader;
    std::unique_ptr<ShaderVertexGL> _vertex_shader;
    std::unique_ptr<ShaderFragmentGL> _fragment_shader;

    std::unique_ptr<GLwrap::Program> _gl;
};

}