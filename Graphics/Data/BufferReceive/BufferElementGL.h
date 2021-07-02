#pragma once

#include <memory>

#include "GLwrap/Buffer.h"

#include "Data/Buffer.h"

namespace Graphics {

class BufferElementGL : public Buffer {
public:
    BufferElementGL(ComponentType data_type, ComponentSize data_size, size_t bytes);
    ~BufferElementGL() override;

    bool write(const void *src, size_t size, size_t offset) override;
    bool read(void *dst, size_t size, size_t offset) override;

    std::shared_ptr<GLwrap::Buffer> data;
};

}