#include "Data/Buffer.h"

#include <cstring>

using namespace Graphics;

Buffer::Buffer(GLwrap::BufferType type, size_t size, const void *ptr) :
    _isGpu(false),
    type(type),
    size(size){

    Cpu cpu = std::make_shared<char[]>(size);
    memcpy(cpu.get(), ptr, size);

    data = cpu;
}

Buffer::~Buffer(){

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