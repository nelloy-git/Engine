#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "glad/gl.h"

#include "GLwrap/BufferAttribute.h"
#include "GLwrap/Vbo.h"
#include "GLwrap/Veo.h"

namespace GLwrap {

enum class VAOdrawMode : GLenum {
    POINTS = GL_POINTS,
    LINE = GL_LINE,
    LINE_LOOP = GL_LINE_LOOP,
    LINE_STRIP = GL_LINE_STRIP,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
};

class VAO {
public:
    VAO();
    virtual ~VAO();

    using AttrList = std::vector<std::shared_ptr<BufferAttrubute>>; 
    void load(const AttrList &attrs, std::shared_ptr<VEO> veo);

    void draw(VAOdrawMode mode, int count, ShaderDataType component, size_t offset = 0);

    void bind();
    void unbind();

    GLuint id();

private:
    GLuint __id;

    AttrList __layouts;
    std::shared_ptr<VEO> __veo;
};

}