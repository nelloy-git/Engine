#pragma once

#include <memory>
#include <vector>

#include "Model/Buffer.h"

namespace Graphics::Model {

class BufferCpu : public Buffer {
public:
    BufferCpu(BufferElemType data_type, BufferElemStruct data_size,
              unsigned int count, unsigned int bytes, bool normalized);
    ~BufferCpu() override;

    bool write(const void *src, unsigned int size, unsigned int offset) override;
    bool read(void *dst, unsigned int size, unsigned int offset) override;

    std::shared_ptr<std::vector<char>> data;
};

}