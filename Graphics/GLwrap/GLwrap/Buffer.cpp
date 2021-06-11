#include "GLwrap/Buffer.h"

#include <stdexcept>

#include "Log.h"

using namespace GLwrap;

Buffer::Buffer(BufferType type, size_t size, BufferUsage usage) : 
    type(type),
    size(size),
    usage(usage){

    glGenBuffers(1, &__id);

    glBindBuffer(static_cast<GLenum>(type), __id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &__id);
}

GLuint Buffer::id(){
    return __id;
}

void Buffer::load(const void* data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    } else if (offset + size > this->size){
        std::string msg = "data is outside of buffer size.";
        LOG(ERR) << msg;
        throw std::invalid_argument(msg);
    }

    glBindBuffer(static_cast<GLenum>(type), __id);
    glBufferSubData(static_cast<GLenum>(type), offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), __id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}