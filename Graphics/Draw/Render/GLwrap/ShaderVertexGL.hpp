#pragma once

#include <string>
#include <vector>

#include "GLwrap/Array.h"
#include "GLwrap/BufferTyped.h"
#include "GLwrap/BufferAccessor.h"
#include "GLwrap/Shader.h"

#include "Draw/Render/GLwrap/PrimitiveGL.hpp"

namespace Graphics::Render {

template<typename T>
class ShaderVertexGL {
public:
    // nullptr for default shader.
    ShaderVertexGL(const std::string &src) :
        gl(GLwrap::ShaderType::Vertex, src){
    };
    virtual ~ShaderVertexGL(){};

    using Input = T;
    // There is only 16 layouts for vec4 vertex attributes. 
    static_assert(sizeof(T) <= 16 * 4 * sizeof(float));
    
    virtual PrimitiveGL<T> *createPrimitive(const std::vector<unsigned int> &indices,
                                            const std::vector<Input> &data) = 0;

    const GLwrap::Shader gl;
};

}