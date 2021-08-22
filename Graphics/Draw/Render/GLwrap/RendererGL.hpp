#pragma once

#include <memory>

#include "GLwrap/Program.h"

#include "Draw/Render/GLwrap/PrimitiveGL.hpp"
#include "Draw/Render/GLwrap/ShaderVertexGL.hpp"
#include "Draw/Render/GLwrap/ShaderFragmentGL.hpp"

namespace Graphics::Render {

template<typename T>
class RendererGL {
public:
    RendererGL(const ShaderVertexGL<T> &vert,
               const ShaderFragmentGL &frag) :
        gl(std::vector{
            &vert.gl,
            &frag.gl,
        }){
    };
    virtual ~RendererGL(){};

    using Input = T;

    virtual void draw(const PrimitiveGL<T> &primitive,
                      const glm::mat4 &pose,
                      const std::vector<float> &morph);

    inline virtual PrimitiveGL<T> *newPrimitive(const std::vector<unsigned int> &indices,
                                                const std::vector<Input> &data) const {
        return _vert->newPrimitive(indices, data);
    };

    GLwrap::Program gl;

private:
    const ShaderVertexGL<T> *_vert;
    const ShaderFragmentGL *_frag;
};

}