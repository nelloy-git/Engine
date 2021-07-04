#pragma once

#include "Data/Types.h"

namespace Graphics {

class Buffer {
public:
    virtual bool write(const void *src, size_t size, size_t offset) = 0;
    virtual bool read(void *dst, size_t size, size_t offset) = 0;

    const ComponentType data_type;
    const ComponentSize data_size;
    const bool normalized;
    const int count;

    const size_t bytes;

protected:
    Buffer(ComponentType data_type, ComponentSize data_size, bool normalized, int count, size_t bytes) :
        data_type(data_type), data_size(data_size), normalized(normalized), count(count), bytes(bytes){
    };
    virtual ~Buffer(){};
};

}