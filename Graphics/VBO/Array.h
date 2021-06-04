#pragma once

#include "glad/glad.h"

#include "VBO/Object.h"
#include "VBO/Types.h"

namespace Graphics::VBO {

class Array : public Object {
public:
    Array(size_t size, UsageType usage) : Object(Graphics::VBO::BufferType::ARRAY, size, usage){};
    virtual ~Array(){};

private:
};

}