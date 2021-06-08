#pragma once

#include <vector>
#include <utility>

#include "glad/gl.h"

#include "GLwrap/Types.h"

namespace Graphics::GLwrap {

class Tex {
public:
    Tex();
    ~Tex();

    void bind();
    void unbind();

    void load(GLsizei width, GLsizei height, const void *data,
              const std::vector<std::pair<Tex2DParamInt, GLuint>> &uint_params = Tex::__default_uint_params);

    const GLuint id;

private:

    static const std::vector<std::pair<Tex2DParamInt, GLuint>> __default_uint_params;
};

}