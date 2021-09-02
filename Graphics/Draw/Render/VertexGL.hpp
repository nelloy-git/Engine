#pragma once

#include <unordered_map>

#include "GLwrap/Array.h"
#include "GLwrap/BufferAccessor.h"

namespace Graphics::Render {

using AccessorsGL = std::unordered_map<GLwrap::BufferArray::Layout, const GLwrap::BufferAccessor *>;

class VertexGL {
public:
    float pos[3];
    float norm[3];
    float tang[3];
    float color[3];
    float tex_coord[2][2];
    float joints[2][4];
    float weights[2][4];

    float morph[8][3];

    float unused[2][4];

    static const AccessorsGL *getAccessors();
};

}