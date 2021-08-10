#include "Draw/ModelData/GLwrap/BufferGL.hpp"

#include <cstring>

#include "Draw/ModelData/GLwrap/TypesGL.h"

#include "Log.h"

using namespace Graphics::Draw;

BufferGL::BufferGL(const Model *model, int index,
                   BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                   size_t elem_count, size_t bytes, bool normalized) : 
    Buffer(model, index, type, data_type, data_size, elem_count, bytes, normalized){

    if (type == BufferType::Other){
        data.emplace<CpuData>(bytes);
    } else {;
        auto gl_accessor = new GLwrap::BufferAccessor(toGLwrap(data_size), toGLwrap(data_type), normalized, 0, 0);
        auto gl_buffer = new GLwrap::Buffer(toGLwrap(type), bytes);
        data.emplace<GpuData>(gl_accessor, gl_buffer);
    }

    // if (type == BufferType::Index){
    //     std::cout << "Buffer vertices: " << elem_count / 3 << std::endl;
    // }
}

BufferGL::~BufferGL(){
}

bool BufferGL::write(const void *src, size_t dst_offset, size_t size){
    if (dst_offset + size > bytes){
        return false;
    }

    if (type == BufferType::Other){
        memcpy(&std::get<CpuData>(data).at(dst_offset), src, size);
        return true;
    } else {
        return std::get<GpuData>(data).gl_data->write(src, dst_offset, size);
    }
}

bool BufferGL::read(void *dst, size_t src_offset, size_t size) const {
    if (src_offset + size > bytes){
        return false;
    }

    if (type == BufferType::Other){
        memcpy(dst, &std::get<CpuData>(data).at(src_offset), size);
        return true;
    } else {
        return std::get<GpuData>(data).gl_data->read(dst, src_offset, size);
    }
}