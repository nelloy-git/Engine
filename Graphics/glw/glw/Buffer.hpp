#pragma once

#include "glad/gl.h"

#include "glw/Utils.hpp"

namespace glw {
    
template<BufferType T, BufferUsage U>
class Buffer {
public:
    Buffer() :
        id(_newId()){
    };

    Buffer(const void *src, GLsizeiptr size) :
        id(_newId()){
        resize(size);
        write(src, 0, size);
    }

    virtual ~Buffer(){
        glDeleteBuffers(1, &id);
    };

    inline void bind() const {
        glBindBuffer(gl(T), id);
    };

    inline virtual void write(const void *src, GLintptr gl_offset, GLsizeiptr size){
        glNamedBufferSubData(id, gl_offset, size, src);
    };

    inline virtual void read(void *dst, GLintptr gl_offset, GLsizeiptr size) const {
        glGetNamedBufferSubData(id, gl_offset, size, dst);
    };

    // Content will be cleared.
    inline virtual void resize(GLsizeiptr size){
        glNamedBufferData(id, size, nullptr, gl(U));
        _size = size;
    }

    inline virtual GLsizeiptr size(){
        return _size;
    }

    const GLuint id;

protected:
    inline static GLuint _newId(){
        GLuint id;
        glGenBuffers(1, &id);
        return id;
    };

    GLsizeiptr _size;
};

}