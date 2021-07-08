#pragma once

#include <memory>

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAccessor.h"

#include "Model/Buffer.h"

namespace Graphics::Model {

class BufferGLwrap : public Buffer {
public:
    BufferGLwrap(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                 unsigned int count, unsigned int bytes, bool normalized);
    ~BufferGLwrap() override;

    bool write(const void *src, unsigned int size, unsigned int offset) override;
    bool read(void *dst, unsigned int size, unsigned int offset) override;

    std::shared_ptr<GLwrap::BufferAccessor> accessor;
    std::shared_ptr<GLwrap::Buffer> data;
};

}