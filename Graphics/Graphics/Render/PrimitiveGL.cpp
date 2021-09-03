#include "Graphics/Render/PrimitiveGL.hpp"

using namespace Graphics::Render;

PrimitiveGL::PrimitiveGL(const std::vector<VertexGL> &data){
    gl_data = std::make_unique<DataGL>(GLwrap::BufferType::Array, data);
    gl_indices = std::unique_ptr<IndicesGL>(nullptr);
    gl_object = std::make_unique<ObjectGL>(gl_data.get(), VertexGL::getAccessors());
};

PrimitiveGL::PrimitiveGL(const std::vector<unsigned int> &indices,
                         const std::vector<VertexGL> &data){
    gl_data = std::make_unique<DataGL>(GLwrap::BufferType::Array, data);
    gl_indices = std::make_unique<IndicesGL>(GLwrap::BufferType::IndexArray, indices);
    gl_object = std::make_unique<ObjectGL>(gl_data.get(), VertexGL::getAccessors(), gl_indices.get());
};

PrimitiveGL *PrimitiveGL::Cube(){
    static const std::vector<Render::VertexGL> cube_data = {
        {.pos = {0, 0, 0}, .color = {0, 1, 0}},
        {.pos = {0, 0, 1}, .color = {0, 1, 0}},
        {.pos = {0, 1, 0}, .color = {0, 1, 0}},
        {.pos = {0, 1, 1}, .color = {0, 1, 0}},
        {.pos = {1, 0, 0}, .color = {0, 1, 0}},
        {.pos = {1, 0, 1}, .color = {0, 1, 0}},
        {.pos = {1, 1, 0}, .color = {0, 1, 0}},
        {.pos = {1, 1, 1}, .color = {0, 1, 0}},
    };

    static const std::vector<unsigned int> cube_indices = {
        0, 2, 3,
        0, 1, 3,
        0, 2, 6,
        0, 6, 4,
        0, 1, 5,
        0, 5, 4,
        7, 6, 4,
        7, 4, 5,
        7, 2, 6,
        7, 3, 2,
        7, 1, 5,
        7, 3, 1
    };
    
    return new PrimitiveGL(cube_indices, cube_data);
}

PrimitiveGL::~PrimitiveGL(){
}