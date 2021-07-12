#pragma once

#include <memory>
#include <vector>

#include "Draw/Buffer.h"

namespace Graphics::Draw {

class BufferCpu : public Buffer {
public:
    BufferCpu(BufferElemType data_type, BufferElemStruct data_size,
              size_t count, size_t bytes, bool normalized);
    ~BufferCpu() override;

    bool write(const void *src, size_t data_offset, size_t data_size) override;
    bool read(void *dst, size_t data_offset, size_t data_size) override;

    std::shared_ptr<std::vector<char>> data;
};

}