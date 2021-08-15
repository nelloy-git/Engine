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
    BufferGL(const Model *model, int index,
             BufferType type, BufferElemType data_type, BufferElemStruct data_size,
             size_t count, size_t bytes, bool normalized);
    ~BufferGL() override;

    bool write(const void *src, size_t dst_offset, size_t size) override;
    bool read(void *dst, size_t src_offset, size_t size) const override;

    using CpuData = std::vector<char>;

    template<typename T>
    struct GpuData {
        GpuData(GLwrap::BufferAccessor *accessor,
                GLwrap::BufferTyped<T> *data) :
            gl_accessor(accessor),
            gl_data(data){};

        GLwrap::BufferAccessor *gl_accessor;
        GLwrap::BufferTyped<T> *gl_data;
    };

    std::variant<CpuData, GpuData<std::any>> data;

};

}