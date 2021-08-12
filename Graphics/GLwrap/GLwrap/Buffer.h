#pragma once

#include "glad/gl.h"

#include "GLwrap/Shader.h"

namespace GLwrap {
    
class Buffer {

public:

    Buffer(BufferType type, size_t size, BufferUsage usage = BufferUsage::STATIC);
    virtual ~Buffer();

    /* if (size == 0){size = this->size;} */
    virtual bool write(const void *data, size_t  offset = 0, size_t size = 0);

    /* if (size == 0){size = this->size;} */
    virtual bool read(void *data, size_t  offset = 0, size_t  size = 0) const;

    void bind() const;
    void unbind() const;

    const GLuint id;
    const size_t size;
    const BufferType type;
    const BufferUsage usage;

private:
    static GLuint _newId();
};

}