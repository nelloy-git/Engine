#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "glad/gl.h"

#include "GLwrap/Accessor.h"
#include "GLwrap/Buffer.h"
#include "GLwrap/Elements.h"

namespace GLwrap {

enum class DrawMode : GLenum {
    POINTS = GL_POINTS,
    LINE = GL_LINE,
    LINE_LOOP = GL_LINE_LOOP,
    LINE_STRIP = GL_LINE_STRIP,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
};

class Array {
public:
    Array();
    virtual ~Array();

    GLuint id();

    bool load(std::shared_ptr<Elements> indices, 
              const std::vector<std::pair<std::shared_ptr<Buffer>,
                                          std::shared_ptr<Accessor>>> &layouts);

    // if (count == 0){count = indices.size / type.size;}
    void draw(DrawMode mode, ComponentType type, int count = 0, size_t offset = 0);

    void bind();
    void unbind();

private:
    GLuint __id = 0;

    std::shared_ptr<Elements> __indices = nullptr;
    std::vector<std::pair<std::shared_ptr<Buffer>,
                          std::shared_ptr<Accessor>>> __layouts;
};

}