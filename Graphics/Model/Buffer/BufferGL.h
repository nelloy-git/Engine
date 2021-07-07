#pragma once

#include <memory>

#include "Model/Buffer.h"

namespace GLwrap {
    class Buffer;
    class BufferAccessor;
}

namespace Graphics::Model {

class BufferGL : public Buffer {
public:
    BufferGL(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
             unsigned int count, unsigned int bytes, bool normalized);
    ~BufferGL() override;

    bool write(const void *src, unsigned int size, unsigned int offset) override;
    bool read(void *dst, unsigned int size, unsigned int offset) override;

    std::shared_ptr<GLwrap::BufferAccessor> accessor;
    std::shared_ptr<GLwrap::Buffer> data;
};

}