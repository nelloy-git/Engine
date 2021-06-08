#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

class VBO : public Buffer {
public:
    VBO(size_t size, BufferUsage usage = BufferUsage::STATIC) : Buffer(BufferType::ARRAY, size, usage){};
    virtual ~VBO(){};
};

}