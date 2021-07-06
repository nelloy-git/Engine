#pragma once

#include <memory>
#include <vector>

#include "Data/Buffer.h"

namespace Graphics {

class BufferCpu : public Buffer {
public:
    BufferCpu(ComponentType data_type, ComponentSize data_size, bool normalized, int count, size_t bytes);
    ~BufferCpu() override;

    bool write(const void *src, size_t size, size_t offset) override;
    bool read(void *dst, size_t size, size_t offset) override;

    std::shared_ptr<std::vector<char>> data;
};

}