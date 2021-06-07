#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace Graphics::GLwrap {

class VBO : public Buffer {
public:
    VBO(size_t size, UsageType usage = UsageType::STATIC) : Buffer(BufferType::ARRAY, size, usage){};
    virtual ~VBO(){};
};

}