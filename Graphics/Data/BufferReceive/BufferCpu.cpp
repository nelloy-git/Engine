#include "Data/BufferReceive/BufferCpu.h"

#include <cstring>

using namespace Graphics;

BufferCpu::BufferCpu(Buffer::ComponentType data_type, Buffer::ComponentSize data_size, size_t bytes) : 
    Buffer(data_type, data_size, bytes){

    data = std::make_shared<char[]>(bytes);
}

BufferCpu::~BufferCpu(){
}

bool BufferCpu::write(const void *src, size_t size, size_t offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(&data[offset], src, size);
    return true;
}

bool BufferCpu::read(void *dst, size_t size, size_t offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(dst, &data[offset], size);
    return true;
}