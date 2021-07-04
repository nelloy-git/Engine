#include "Data/Buffer/BufferCpu.h"

#include <cstring>

using namespace Graphics;

BufferCpu::BufferCpu(ComponentType data_type, ComponentSize data_size, bool normalized, int count, size_t bytes) : 
    Buffer(data_type, data_size, normalized, count, bytes){
    
    data = std::make_shared<std::vector<char>>(bytes);
}

BufferCpu::~BufferCpu(){
}

bool BufferCpu::write(const void *src, size_t size, size_t offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(&data->at(offset), src, size);
    return true;
}

bool BufferCpu::read(void *dst, size_t size, size_t offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(dst, &data->at(offset), size);
    return true;
}