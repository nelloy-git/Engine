#include "GLwrap/Accessor.h"

using namespace GLwrap;

Accessor::Accessor(GLuint location,
                   ComponentSize size, ComponentType type,
                   bool normalized, size_t step, size_t offset):
    location(location),
    component_size(size),
    component_type(type),
    normalized(normalized),
    step(step == 0 ? static_cast<GLuint>(size) * getDataTypeSize(type) : step),
    offset(offset){
}

Accessor::~Accessor(){
    
}

void Accessor::enable(const Buffer &buffer){
    buffer.bind();

    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location,
                          static_cast<GLuint>(component_size),
                          static_cast<GLenum>(component_type),
                          normalized ? GL_TRUE : GL_FALSE,
                          step, (void*)offset);

    buffer.unbind();
}

void Accessor::disable(const Buffer &buffer){
    buffer.bind();
    glDisableVertexAttribArray(location);
    buffer.unbind();
}