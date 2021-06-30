#pragma once

#include <variant>

#include "GLwrap/Buffer.h"

namespace Graphics {

class Buffer {
public:
    using Gpu = std::shared_ptr<GLwrap::Buffer>;
    using Cpu = std::shared_ptr<char[]>;

public:
    Buffer(GLwrap::BufferType type, size_t size, const void *ptr);
    virtual ~Buffer();

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