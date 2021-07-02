#include "Data/BufferReceive/BufferElementGL.h"

#include <cstring>

using namespace Graphics;

BufferElementGL::BufferElementGL(Buffer::ComponentType data_type, Buffer::ComponentSize data_size, size_t bytes) : 
    Buffer(data_type, data_size, bytes){

    data = std::make_shared<GLwrap::Buffer>(GLwrap::BufferType::ELEMENT_ARRAY, bytes);
}

BufferElementGL::~BufferElementGL(){
}

bool BufferElementGL::write(const void *src, size_t size, size_t offset){
    return data->write(src, offset, size);
}

bool BufferElementGL::read(void *dst, size_t size, size_t offset){
    return data->read(dst, offset, size);
}