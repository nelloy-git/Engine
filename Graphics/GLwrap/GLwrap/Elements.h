#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

class Elements : public Buffer {
public:
    Elements(size_t size, BufferUsage usage = BufferUsage::STATIC) : Buffer(BufferType::ELEMENT_ARRAY, size, usage){};
    virtual ~Elements(){};

    int count();
};

}