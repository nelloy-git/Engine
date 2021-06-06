#pragma once

#include <vector>

#include "glad/glad.h"

#include "GLwrap/Buffer.h"

namespace Graphics::GLwrap {

struct VAOdata {
    ShaderDataSize size;
    ShaderDataType type;
    const Buffer *buff;
};

class VAO {
public:
    VAO();
    virtual ~VAO();

    void attrib(std::vector<VAOdata> &list);

    void bind();
    void unbind();

    const GLuint id;
};

}