#pragma once

#include <memory>

#include "glad/glad.h"

#include "VBO/utils/DataType.h"
#include "VBO/utils/UsageType.h"

namespace Graphics::VBO {

class Object {
public:
    Object(DataType type);
    virtual ~Object();

    void load(const size_t size, const void* ptr, UsageType usage);

    virtual void bind();
    virtual void unbind();

    const GLuint id;
    const DataType type;

    const void* ptr();
    int size();
    UsageType usage();

protected:
    const void* __ptr;
    GLsizeiptr __size;
    UsageType __usage;
};

}