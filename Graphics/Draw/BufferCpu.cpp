#include "Draw/BufferCpu.h"

#include <cstring>

#include "Log.h"

using namespace Graphics::Draw;

BufferCpu::BufferCpu(BufferElemType data_type, BufferElemStruct data_size,
                     size_t count, size_t bytes, bool normalized) : 
    Buffer(BufferType::Other, data_type, data_size, count, bytes, normalized){
    
    data = std::make_shared<std::vector<char>>(bytes);
}

BufferCpu::~BufferCpu(){
}

bool BufferCpu::write(const void *src, size_t data_offset, size_t data_size){
    if (data_size + data_offset > bytes){
        return false;
    }

    memcpy(&data->at(data_offset), src, data_size);
    return true;
}

bool BufferCpu::read(void *dst, size_t data_offset, size_t data_size){
    if (data_size + data_offset > bytes){
        return false;
    }
    memcpy(dst, &data->at(data_offset), data_size);
    return true;
}