#pragma once

#include "glad/gl.h"

#include "GLwrap/Types.h"

namespace Graphics::GLwrap {
    
class Buffer {
public:
    Buffer(BufferType type, size_t size, UsageType usage = UsageType::STATIC);
    virtual ~Buffer();

    // if (size == 0){size = this->size}
    void load(const void* data, int offset = 0, size_t size = 0);

    // if (step == 0){step = attr_size * sizeof(attr_type)}
    void attrib(GLuint attr_id,
                ShaderDataSize attr_size, ShaderDataType attr_type,
                size_t step = 0, size_t offset = 0);

    void bind() const;
    void unbind() const;

    const GLuint id;
    const BufferType type;
    size_t size;
    UsageType usage;
};

}