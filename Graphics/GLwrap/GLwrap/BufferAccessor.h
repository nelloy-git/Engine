#pragma once

#include <memory>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"
#include "GLwrap/Shader.h"

namespace GLwrap {

class BufferAccessor {
public:

    // if (step == 0){step = size * sizeof(type)}
    BufferAccessor(ComponentSize size, ComponentType type,
                   bool normalized, size_t step, size_t offset);
    ~BufferAccessor();

    // Enable accessor for binded buffer.
    void enable(GLuint location);

    const ComponentSize component_size;
    const ComponentType component_type;
    const bool normalized;
    const size_t step;
    const size_t offset;

private:
};

}