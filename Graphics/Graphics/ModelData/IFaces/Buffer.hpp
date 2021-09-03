#pragma once

#include <stddef.h>
#include <vector>

#include "Graphics/Types.h"

#include "Graphics/ModelData/IFaces/ModelData.h"

namespace Graphics::Draw {

class Model;

class Buffer : public ModelData {
public:
    Buffer(const Model *model, int index,
           BufferType type, BufferElemType data_type, BufferElemStruct data_struct,
           size_t count, size_t bytes, bool normalized) :
        ModelData(model, index),
        type(type), 
        data_type(data_type),
        data_size(data_size),
        count(count),
        bytes(bytes),
        normalized(normalized){
    };

    virtual ~Buffer(){
    };

    virtual bool write(const void *src, size_t dst_offset, size_t size) = 0;
    virtual bool read(void *dst, size_t src_offset, size_t size) const = 0;

    template<typename T>
    T readElement(unsigned int i) const {
        T buf;
        read(&buf, i * sizeof(T), sizeof(T));
        return buf;
    };

    const BufferType type;
    const BufferElemType data_type;
    const BufferElemStruct data_size;
    const bool normalized;
    const size_t count;
    const size_t bytes;

protected:
};

}