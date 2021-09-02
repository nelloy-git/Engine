#include "Draw/Render/PrimitiveGL.hpp"

using namespace Graphics::Render;

PrimitiveGL::PrimitiveGL(const std::vector<VertexGL> &data){
    gl_data = std::make_unique<DataGL>(GLwrap::BufferType::Array, data);
    gl_indices = std::unique_ptr<IndicesGL>(nullptr);
    gl_object = std::make_unique<ObjectGL>(*gl_data, *VertexGL::getAccessors());
};

PrimitiveGL::PrimitiveGL(const std::vector<unsigned int> &indices,
                         const std::vector<VertexGL> &data){
    gl_data = std::make_unique<DataGL>(GLwrap::BufferType::Array, data);
    gl_indices = std::make_unique<IndicesGL>(GLwrap::BufferType::IndexArray, indices);
    gl_object = std::make_unique<ObjectGL>(*gl_data, *VertexGL::getAccessors(), *gl_indices);
};

PrimitiveGL::~PrimitiveGL(){
}