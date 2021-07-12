#include "GLwrap/Buffer.h"

#include <stdexcept>

#include "Log.h"

using namespace GLwrap;

Buffer::Buffer(BufferType type, size_t size, BufferUsage usage) : 
    type(type),
    size(size),
    usage(usage){

    glGenBuffers(1, &_id);

    glBindBuffer(static_cast<GLenum>(type), _id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Buffer::~Buffer(){
    glDeleteBuffers(1, &_id);
}

GLuint Buffer::id(){
    return _id;
}

bool Buffer::write(const void *data, size_t data_offset, size_t data_size){
    if (data_size == 0){
        data_size = size;
    }
    
    if (data_offset + data_size > size){
        LOG(WRN) << "Write outside of buffer ("
                 << "offset: " << data_offset << ", "
                 << "data size: " << data_size << ", "
                 << "buffer size: " << size << ").";
        return false;
    }

    glBindBuffer(static_cast<GLenum>(type), _id);
    glBufferSubData(static_cast<GLenum>(type), data_offset, data_size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
    return true;
}

bool Buffer::read(void *data, size_t data_offset, size_t data_size){
    if (data_size == 0){
        data_size = size;
    }
    
    if (data_offset + data_size > size){
        LOG(WRN) << "Read outside of buffer ("
                 << "offset: " << data_offset << ", "
                 << "data size: " << data_size << ", "
                 << "buffer size: " << size << ").";
        return false;
    }

    glGetNamedBufferSubData(_id, data_offset, data_size, data);
    return true;
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), _id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}