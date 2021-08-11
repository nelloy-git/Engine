#pragma once

#include <string>
#include <vector>

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAccessor.h"
#include "GLwrap/Shader.h"

#include "Draw/Render/ShaderIFaces.hpp"

namespace Graphics::Render {

template<typename T>
class ShaderInputGL : public ShaderInput {
public:
    // nullptr for default shader.
    ShaderInputGL(const std::string *src = nullptr);
    virtual ~ShaderInputGL();

    using Input = T;
    static_assert(sizeof(T) <= 16 * 4 * sizeof(float));

    static GLwrap::Buffer *createBuffer(const std::vector<Input> &data){
        auto buff = new GLwrap::Buffer(GLwrap::BufferType::Array,
                                       data.size() * sizeof(Input));
        buff->write(&data[0]);
        return buff;
    };

    static virtual const std::vector<const GLwrap::BufferAccessor> &getAccessors() = 0;

    const GLwrap::Shader gl;
};

}