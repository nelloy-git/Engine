#include "Model/GLwrap/BufferGLwrap.h"

#include "Model/GLwrap/TypesGLwrap.h"

#include "Log.h"

using namespace Graphics::Model;

BufferGLwrap::BufferGLwrap(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                   unsigned int count, unsigned int bytes, bool normalized) : 
    Buffer(type, data_type, data_size, normalized, count, bytes){

    accessor = std::make_shared<GLwrap::BufferAccessor>(toGLwrap(data_size), toGLwrap(data_type), normalized, 0, 0);
    data = std::make_shared<GLwrap::Buffer>(toGLwrap(type), bytes);
}

BufferGLwrap::~BufferGLwrap(){
}

bool BufferGLwrap::write(const void *src, unsigned int size, unsigned int offset){
    return data->write(src, offset, size);
}

bool BufferGLwrap::read(void *dst, unsigned int size, unsigned int offset){
    return data->read(dst, offset, size);
}