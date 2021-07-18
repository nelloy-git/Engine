#pragma once

#include <stddef.h>

#include "GLwrap/Types.h"

#include "Draw/Types.h"

namespace Graphics::Draw {

class Model;

class Buffer {
public:
    const Model &model;
    const int index;

    virtual bool write(const void *src, size_t dst_offset, size_t size) = 0;
    virtual bool read(void *dst, size_t src_offset, size_t size) = 0;

    const BufferType type;
    const BufferElemType data_type;
    const BufferElemStruct data_size;
    const bool normalized;
    const size_t count;
    const size_t bytes;

protected:
    Buffer(const Model &model, int index,
           BufferType type, BufferElemType data_type, BufferElemStruct data_struct,
           size_t count, size_t bytes, bool normalized);
    virtual ~Buffer();
};

}