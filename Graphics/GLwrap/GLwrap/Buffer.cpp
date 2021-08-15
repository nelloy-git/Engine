#include "GLwrap/Buffer.h"

#include <stdexcept>
#include <iostream>

using namespace GLwrap;

Buffer::Buffer(BufferType type, size_t size, BufferUsage usage) : 
    id(_newId()),
    type(type),
    bytes(size),
    usage(usage){

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &id);
}

bool Buffer::write(const void *data, size_t data_offset, size_t data_size){
    if (data_size == 0){
        data_size = bytes;
    }
    
    if (data_offset + data_size > bytes){
        std::cout << "Write outside of buffer ("
                  << "offset: " << data_offset << ", "
                  << "data size: " << data_size << ", "
                  << "buffer size: " << bytes << ")."
                  << std::endl;
        return false;
    }

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferSubData(static_cast<GLenum>(type), data_offset, data_size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
    return true;
}

bool Buffer::read(void *data, size_t data_offset, size_t data_size) const {
    if (data_size == 0){
        data_size = bytes;
    }
    
    if (data_offset + data_size > bytes){
        std::cout << "Read outside of buffer ("
                  << "offset: " << data_offset << ", "
                  << "data size: " << data_size << ", "
                  << "buffer size: " << bytes << ")."
                  << std::endl;;
        return false;
    }

    glGetNamedBufferSubData(id, data_offset, data_size, data);
    return true;
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}

GLuint Buffer::_newId(){
    GLuint id;
    glGenBuffers(1, &id);
    return id;
}