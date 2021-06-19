#include "GLwrap/BufferAccessor.h"

using namespace GLwrap;

BufferAccessor::BufferAccessor(
                ComponentSize size, ComponentType type,
                bool normalized, size_t step, size_t offset):
    component_size(size),
    component_type(type),
    normalized(normalized),
    step(step),
    offset(offset){
}

BufferAccessor::~BufferAccessor(){
    
}

void BufferAccessor::enable(GLuint location){
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location,
                          static_cast<GLuint>(component_size),
                          static_cast<GLenum>(component_type),
                          normalized ? GL_TRUE : GL_FALSE,
                          step, (void*)offset);
}