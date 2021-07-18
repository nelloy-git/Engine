#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAccessor.h"

#include "Draw/ModelData/IFaces/Buffer.hpp"

namespace Graphics::Draw {

class BufferGL : public Buffer {
public:
    BufferGL(const Model &model, int index,
             BufferType type, BufferElemType data_type, BufferElemStruct data_size,
             size_t count, size_t bytes, bool normalized);
    ~BufferGL() override;

    bool write(const void *src, size_t dst_offset, size_t size) override;
    bool read(void *dst, size_t src_offset, size_t size) override;

    using CpuData = std::vector<char>;
    using GpuData = struct {
        std::shared_ptr<GLwrap::BufferAccessor> gl_accessor;
        std::shared_ptr<GLwrap::Buffer> gl_data;
    };

    std::variant<CpuData, GpuData> data;

private:

};

}