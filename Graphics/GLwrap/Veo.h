#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace Graphics::GLwrap {

class VEO : public Buffer {
public:
    VEO(size_t size, UsageType usage = UsageType::STATIC) : Buffer(BufferType::ELEMENT_ARRAY, size, usage){};
    virtual ~VEO(){};
};

}