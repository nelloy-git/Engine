#include "Draw/Loader/toGLwrap/BufferGLwrap.h"

#include "Draw/Loader/toGLwrap/TypesGLwrap.h"

#include "Log.h"

using namespace Graphics::Draw;

BufferGLwrap::BufferGLwrap(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                           size_t elem_count, size_t bytes, bool normalized) : 
    Buffer(type, data_type, data_size, elem_count, bytes, normalized){

    accessor = std::make_shared<GLwrap::BufferAccessor>(toGLwrap(data_size), toGLwrap(data_type), normalized, 0, 0);
    data = std::make_shared<GLwrap::Buffer>(toGLwrap(type), bytes);
}

BufferGLwrap::~BufferGLwrap(){
}

bool BufferGLwrap::write(const void *src, size_t data_offset, size_t data_size){
    return data->write(src, data_offset, data_size);
}

bool BufferGLwrap::read(void *dst, size_t data_offset, size_t data_size){
    return data->read(dst, data_offset, data_size);
}