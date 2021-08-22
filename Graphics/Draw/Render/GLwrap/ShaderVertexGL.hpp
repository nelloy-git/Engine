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

    // There is only 16 layouts for vec4 vertex attributes. 
    using Input = T;
    static_assert(sizeof(T) <= 16 * 4 * sizeof(float));

    using AccessorsGL = std::unordered_map<GLwrap::BufferArray::Layout, const GLwrap::BufferAccessor *>;
    
    virtual PrimitiveGL<T> *newPrimitive(const std::vector<unsigned int> &indices,
                                         const std::vector<Input> &data) const {
        GLwrap::BufferTyped<Input> gl_data(GLwrap::BufferType::Array, data);
        auto &gl_accessors = getAccessors();
        GLwrap::BufferTyped<unsigned int> gl_indices(GLwrap::BufferType::IndexArray, indices);

        return new PrimitiveGL(gl_data, gl_accessors, gl_indices);
    }

    virtual const AccessorsGL &getAccessors() const = 0;

    const GLwrap::Shader gl;
};

}