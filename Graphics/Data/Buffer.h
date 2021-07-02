#pragma once

#include "Data/Types.h"

namespace Graphics {

class Buffer {
public:
    Buffer(ComponentType data_type, ComponentSize data_size, size_t bytes) :
        data_type(data_type), data_size(data_size), bytes(bytes){
    };
    virtual ~Buffer() = 0;

    virtual bool write(const void *src, size_t size, size_t offset) = 0;
    virtual bool read(void *dst, size_t size, size_t offset) = 0;

    const ComponentType data_type;
    const ComponentSize data_size;
    const size_t bytes;
};

}