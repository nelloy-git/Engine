#pragma once

#include <variant>

#include "GLwrap/Buffer.h"

namespace Graphics {

class Buffer {
public:
    using Gpu = std::shared_ptr<GLwrap::Buffer>;
    using Cpu = std::shared_ptr<char[]>;

public:
    Buffer(GLwrap::BufferType type, size_t size);
    virtual ~Buffer();

    bool write(void *src, int offset = 0, size_t size = 0);
    bool read(void *dst, int offset = 0, size_t size = 0);

    bool isGpu();
    void toGpu();
    void fromGpu();

    GLwrap::BufferType type;
    size_t size;
    std::variant<Cpu, Gpu> data;

private:
    bool _isGpu = false;
};

}