#pragma once

#include "glad/gl.h"

#include "GLwrap/Shader.h"

namespace GLwrap {

enum class BufferType : GLenum {
    ARRAY = GL_ARRAY_BUFFER,
    ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
};

enum class BufferUsage : GLenum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
};
    
class Buffer {

public:
    struct Attrib {
        Attrib(GLuint attr_id,
               ShaderDataSize attr_size, ShaderDataType attr_type,
               size_t step = 0, size_t offset = 0){
            id = attr_id;
            size = attr_size;
            type = attr_type;
            step = step;
            offset = offset;
        }

        GLuint id;
        ShaderDataSize size;
        ShaderDataType type;
        size_t step = 0;
        size_t offset = 0;
    };

    Buffer(BufferType type, size_t size, BufferUsage usage = BufferUsage::STATIC);
    virtual ~Buffer();

    // if (size == 0){size = this->size}
    void load(const void* data, int offset = 0, size_t size = 0);

    // if (step == 0){step = attr_size * sizeof(attr_type)}
    void attrib(GLuint attr_id,
                ShaderDataSize attr_size, ShaderDataType attr_type,
                size_t step = 0, size_t offset = 0);
    void attrib(const Attrib &attr);

    void bind() const;
    void unbind() const;

    GLuint id();
    const size_t size;
    const BufferType type;
    const BufferUsage usage;

private:
    GLuint __id;
};

}