#include "Model/Buffer/BufferCpu.h"

#include <cstring>

using namespace Graphics::Model;

BufferCpu::BufferCpu(BufferElemType data_type, BufferElemStruct data_size,
                     unsigned int count, unsigned int bytes, bool normalized) : 
    Buffer(BufferType::Other, data_type, data_size, normalized, count, bytes){
    
    data = std::make_shared<std::vector<char>>(bytes);
}

BufferCpu::~BufferCpu(){
}

bool BufferCpu::write(const void *src, unsigned int size, unsigned int offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(&data->at(offset), src, size);
    return true;
}

bool BufferCpu::read(void *dst, unsigned int size, unsigned int offset){
    if (size + offset > bytes){
        return false;
    }
    memcpy(dst, &data->at(offset), size);
    return true;
}