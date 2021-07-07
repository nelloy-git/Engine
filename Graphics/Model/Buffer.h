#pragma once

#include "GLwrap/Types.h"

#include "Model/Types.h"

namespace Graphics::Model {

class Buffer {
public:
    virtual bool write(const void *src, unsigned int size, unsigned int offset) = 0;
    virtual bool read(void *dst, unsigned int size, unsigned int offset) = 0;

    const BufferType type;
    const BufferElemType data_type;
    const BufferElemStruct data_size;
    const bool normalized;
    const unsigned int count;
    const unsigned int bytes;

protected:
    Buffer(BufferType type, BufferElemType data_type, BufferElemStruct data_struct,
           unsigned int count, unsigned int bytes, bool normalized) :
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