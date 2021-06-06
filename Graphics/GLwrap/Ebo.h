#pragma once

#include "glad/glad.h"

#include "GLwrap/Buffer.h"

namespace Graphics::GLwrap {

class EBO : public Buffer {
public:
    EBO(size_t size, UsageType usage = UsageType::STATIC) : Buffer(BufferType::ELEMENT_ARRAY, size, usage){};
    virtual ~EBO(){};
};

}