#include "Data/Buffer/BufferElementGL.h"

#include <cstring>

using namespace Graphics;

BufferElementGL::BufferElementGL(ComponentType data_type, ComponentSize data_size, bool normalized, int count, size_t bytes) : 
    Buffer(data_type, data_size, normalized, count, bytes){

    data = std::make_shared<GLwrap::Buffer>(GLwrap::BufferType::IndexArray, bytes);
}

BufferElementGL::~BufferElementGL(){
}

bool BufferElementGL::write(const void *src, size_t size, size_t offset){
    return data->write(src, offset, size);
}

bool BufferElementGL::read(void *dst, size_t size, size_t offset){
    return data->read(dst, offset, size);
}