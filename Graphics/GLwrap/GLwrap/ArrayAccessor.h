#pragma once

#include "GLwrap/Array.h"
#include "GLwrap/Types.h"

namespace GLwrap {

class ArrayAccessor {
public:
    ArrayAccessor(DrawMode mode, ComponentType type, size_t vertex_count, size_t byte_offset);
    virtual ~ArrayAccessor();

    void draw();

    const DrawMode mode;
    const ComponentType type;
    const size_t vertex_count;
    const size_t byte_offset;
};

}