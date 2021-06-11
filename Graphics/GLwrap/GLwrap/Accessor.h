#pragma once

#include <memory>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"
#include "GLwrap/Shader.h"

namespace GLwrap {

class Accessor {
public:

    // if (step == 0){step = size * sizeof(type)}
    Accessor(GLuint location,
             ComponentSize size, ComponentType type,
             bool normalized, size_t step = 0, size_t offset = 0);
    ~Accessor();

    void enable(const Buffer &buffer);
    void disable(const Buffer &buffer);

    const GLuint location;
    const ComponentSize component_size;
    const ComponentType component_type;
    const bool normalized;
    const size_t step;
    const size_t offset;

private:
};

}