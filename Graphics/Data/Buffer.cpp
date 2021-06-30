#include "Data/Buffer.h"

#include <cstring>

using namespace Graphics;

Buffer::Buffer(GLwrap::BufferType type, size_t size, const void *ptr) :
    isGpu(false),
    type(type),
    size(size){

    Cpu cpu = std::make_shared<char[]>(size);
    memcpy(cpu.get(), ptr, size);

    data = cpu;
}

Buffer::~Buffer(){

}

void Buffer::toGpu(){
    if (isGpu){
        return;
    }

    Cpu cpu = std::get<Cpu>(data);
    Gpu gpu = std::make_shared<GLwrap::Buffer>(type, size);
    data = gpu;
    isGpu = true;

    gpu->write(cpu.get());
}

void Buffer::fromGpu(){
    if (!isGpu){
        return;
    }

    Gpu gpu = std::get<Gpu>(data);
    Cpu cpu = std::make_shared<char[]>(size);
    data = cpu;
    isGpu = false;

    gpu->read(cpu.get());
}