#include "Data/BufferReceive/BufferVertexGL.h"

#include <cstring>

using namespace Graphics;

BufferVertexGL::BufferVertexGL(ComponentType data_type, ComponentSize data_size, size_t bytes) : 
    Buffer(data_type, data_size, bytes){

    data = std::make_shared<GLwrap::Buffer>(GLwrap::BufferType::ARRAY, bytes);
}

BufferVertexGL::~BufferVertexGL(){
}

bool BufferVertexGL::write(const void *src, size_t size, size_t offset){
    return data->write(src, offset, size);
}

bool BufferVertexGL::read(void *dst, size_t size, size_t offset){
    return data->read(dst, offset, size);
}