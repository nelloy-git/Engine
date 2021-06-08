#pragma once

#include <vector>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

class VAO {
public:
    VAO();
    virtual ~VAO();

    void bind();
    void unbind();

    const GLuint id;
};

}