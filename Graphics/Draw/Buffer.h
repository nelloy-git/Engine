#pragma once

#include <stddef.h>

#include "GLwrap/Types.h"

#include "Draw/Types.h"

namespace Graphics::Draw {

class Buffer {
public:
    virtual bool write(const void *src, size_t data_offset, size_t data_size) = 0;
    virtual bool read(void *dst, size_t data_offset, size_t data_size) = 0;

    const BufferType type;
    const BufferElemType data_type;
    const BufferElemStruct data_size;
    const bool normalized;
    const size_t count;
    const size_t bytes;

protected:
    Buffer(BufferType type, BufferElemType data_type, BufferElemStruct data_struct,
           size_t count, size_t bytes, bool normalized) :
        type(type), 
        data_type(data_type),
        data_size(data_size),
        count(count),
        bytes(bytes),
        normalized(normalized){
    };
    virtual ~Buffer(){};
};

}