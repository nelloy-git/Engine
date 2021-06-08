#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

class VEO : public Buffer {
public:
    VEO(size_t size, BufferUsage usage = BufferUsage::STATIC) : Buffer(BufferType::ELEMENT_ARRAY, size, usage){};
    virtual ~VEO(){};
};

}