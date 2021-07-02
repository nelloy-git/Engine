#pragma once

#include <memory>

#include "GLwrap/Buffer.h"

#include "Data/Buffer.h"

namespace Graphics {

class BufferVertexGL : public Buffer {
public:
    BufferVertexGL(ComponentType data_type, ComponentSize data_size, size_t bytes);
    ~BufferVertexGL() override;

    bool write(const void *src, size_t size, size_t offset) override;
    bool read(void *dst, size_t size, size_t offset) override;

    std::shared_ptr<GLwrap::Buffer> data;
};

}