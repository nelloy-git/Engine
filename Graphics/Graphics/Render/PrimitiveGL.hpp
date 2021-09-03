#pragma once

#include <vector>

#include "GLwrap/BufferTyped.h"

#include "Graphics/Render/VertexGL.hpp"

namespace Graphics::Render {

using DataGL = GLwrap::BufferTyped<VertexGL>;
using IndicesGL = GLwrap::BufferTyped<unsigned int>;
using ObjectGL = GLwrap::BufferArray;

class PrimitiveGL {
template<typename T>
friend class ShaderVertexGL;
public:
    explicit PrimitiveGL(const std::vector<VertexGL> &data);
    PrimitiveGL(const std::vector<unsigned int> &indices,
                const std::vector<VertexGL> &data);

    static PrimitiveGL *Cube();

    virtual ~PrimitiveGL();

    std::unique_ptr<DataGL> gl_data;
    std::unique_ptr<IndicesGL> gl_indices;
    std::unique_ptr<ObjectGL> gl_object;

    GLwrap::DrawMode gl_draw_mode = GLwrap::DrawMode::Triangles;
};

}