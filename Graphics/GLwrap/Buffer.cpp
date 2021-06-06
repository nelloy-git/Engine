#include "GLwrap/Buffer.h"

using namespace Graphics::GLwrap;

Buffer::Buffer(BufferType type, size_t size, UsageType usage) :
    id(0),
    type(type),
    size(size),
    usage(usage){

    auto pId = const_cast<GLuint*>(&id);
    glGenBuffers(1, pId);

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &id);
}

void Buffer::load(const void* data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferSubData(static_cast<GLenum>(type), offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}