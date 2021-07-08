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

bool Buffer::write(const void *data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }
    
    if (offset + size > this->size){
        LOG(WRN) << "Data is outside of buffer size.\n"
                 << "Buffer size: " << this->size << "\n"
                 << "Data size: " << size;
        return false;
    }

    glBindBuffer(static_cast<GLenum>(type), _id);
    glBufferSubData(static_cast<GLenum>(type), offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
    return true;
}

bool Buffer::read(void *data, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }
    
    if (offset + size > this->size){
        LOG(WRN) << "Data is outside of buffer size.";
        return false;
    }

    glGetBufferSubData(_id, offset, size, data);
    return true;
}

void Buffer::bind() const {
    glBindBuffer(static_cast<GLenum>(type), _id);
}

void Buffer::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}