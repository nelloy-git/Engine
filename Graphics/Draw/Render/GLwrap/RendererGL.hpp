#pragma once

#include <memory>

#include "GLwrap/Program.h"

#include "Draw/Render/Renderer.hpp"
#include "Draw/Render/GLwrap/ShaderVertexGL.hpp"
#include "Draw/Render/GLwrap/ShaderFragmentGL.hpp"

namespace Graphics::Render {

template<typename T>
class RendererGL : public Renderer {
public:
    RendererGL(const ShaderVertexGL<T> &vert,
               const ShaderFragmentGL &frag) :
        Renderer(),
        gl(std::vector{
            &vert.gl,
            &frag.gl,
        }){
    };
    virtual ~RendererGL(){};

    GLwrap::Program gl;
};

}