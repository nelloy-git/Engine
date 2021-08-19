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
                                            const std::vector<Input> &data){
        BufferTyped<Input> gl_data(BufferType::Array, data);
        auto &gl_accessors = getAccessors();
        BufferTyped<unsigned int> gl_indices(BufferType::IndexArray, indices);

        return new PrimitiveGL(gl_data, gl_accessors, gl_indices);
    }

    virtual const std::unordered_map<BufferArray::Layout, const BufferAccessor *> &getAccessors() = 0;

    const GLwrap::Shader gl;
};

}