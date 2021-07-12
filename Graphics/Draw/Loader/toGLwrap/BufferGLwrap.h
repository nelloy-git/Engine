#pragma once

#include <memory>

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAccessor.h"

#include "Draw/Buffer.h"

namespace Graphics::Draw {

class BufferGLwrap : public Buffer {
public:
    BufferGLwrap(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                 size_t count, size_t bytes, bool normalized);
    ~BufferGLwrap() override;

    bool write(const void *src, size_t data_offset, size_t data_size) override;
    bool read(void *dst, size_t data_offset, size_t data_size) override;

    std::shared_ptr<GLwrap::BufferAccessor> accessor;
    std::shared_ptr<GLwrap::Buffer> data;
};

}