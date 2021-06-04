#pragma once

#include <memory>

#include "glad/glad.h"

#include "VBO/Types.h"

namespace Graphics::VBO {

class Object {
public:
    Object(BufferType type, size_t size, UsageType usage);
    virtual ~Object();

    void load(int bytes_offset, size_t size, const void* data);

    // virtual void bind();
    // virtual void unbind();

    virtual void bind() const;
    virtual void unbind() const;

    const GLuint id;
    const BufferType type;
    size_t size;
    UsageType usage;

protected:
};

}