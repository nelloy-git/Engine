#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "GLwrap/Program.h"

#include "Graphics/Render/PrimitiveGL.hpp"
#include "Graphics/Render/VertexShaderGL.hpp"
#include "Graphics/Render/FragmentShaderGL.hpp"

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