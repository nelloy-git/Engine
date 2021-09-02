#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "GLwrap/Program.h"

#include "Draw/Render/PrimitiveGL.hpp"
#include "Draw/Render/VertexShaderGL.hpp"
#include "Draw/Render/FragmentShaderGL.hpp"

namespace Graphics::Render {

class RendererGL {
public:
    RendererGL(const VertexShaderGL &vert, const FragmentShaderGL &frag);
    virtual ~RendererGL();

    virtual void draw(const PrimitiveGL &primitive,
                      const glm::mat4 &pose,
                      const std::vector<float> &morph);

    std::unique_ptr<GLwrap::Program> gl;
};

}