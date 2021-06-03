#include "GLSL/Attribute/VertexArray.h"

using namespace Graphics::GLSL::Attribute;

VertexArray::VertexArray(const std::shared_ptr<Program> program, const std::string& attr_name,
                         const std::shared_ptr<VBO::Array> vbo,
                         const DataSize size, const DataType type, const bool normalize,
                         const GLsizei step, const int offset) :
    Base(program, attr_name),
    vbo(vbo),
    size(size),
    type(type),
    normalize(normalize),
    step(step),
    offset(offset){

    vbo->bind();
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, static_cast<GLint>(size), static_cast<GLenum>(type),
                          normalize ? GL_TRUE : GL_FALSE,
                          step, (void*)(offset));
    vbo->unbind();
}