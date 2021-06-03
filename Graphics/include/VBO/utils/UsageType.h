#pragma once

#include "glad/glad.h"

namespace Graphics::VBO {

enum class UsageType : GLenum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
};

}