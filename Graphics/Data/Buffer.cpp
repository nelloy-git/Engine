#include "Data/Buffer.h"

#include <cstring>

#include "Log.h"

using namespace Graphics;

Buffer::Buffer(GLwrap::BufferType type, size_t size) :
    _isGpu(false),
    type(type),
    size(size){

    Cpu cpu = std::make_shared<char[]>(size);

    data = cpu;
}

Buffer::~Buffer(){

}

bool Buffer::write(void *src, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }
    
    if (offset + size > this->size){
        LOG(WRN) << "Data is outside of buffer size.";
        return false;
    }

    if (_isGpu){
        auto gpu = std::get<Gpu>(data);
        return gpu->write(src, offset, size);
    } else {
        auto cpu = std::get<Cpu>(data);
        memcpy(&cpu[offset], src, size);
        return true;
    }
}

bool Buffer::read(void *dst, int offset, size_t size){
    if (size == 0){
        size = this->size;
    }
    
    if (offset + size > this->size){
        LOG(WRN) << "Data is outside of buffer size.";
        return false;
    }

    if (_isGpu){
        auto gpu = std::get<Gpu>(data);
        return gpu->read(dst, offset, size);
    } else {
        auto cpu = std::get<Cpu>(data);
        memcpy(dst, &cpu[offset], size);
        return true;
    }
}

bool Buffer::isGpu(){
    return _isGpu;
}

void Buffer::toGpu(){
    if (_isGpu){
        return;
    }

    Cpu cpu = std::get<Cpu>(data);
    Gpu gpu = std::make_shared<GLwrap::Buffer>(type, size);
    data = gpu;
    _isGpu = true;

    gpu->write(cpu.get());
}

void Buffer::fromGpu(){
    if (!_isGpu){
        return;
    }

    Gpu gpu = std::get<Gpu>(data);
    Cpu cpu = std::make_shared<char[]>(size);
    data = cpu;
    _isGpu = false;

    gpu->read(cpu.get());
}