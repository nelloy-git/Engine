#include "GLwrap/ArrayAccessor.h"

using namespace GLwrap;

ArrayAccessor::ArrayAccessor(DrawMode mode, ComponentType type, size_t vertex_count, size_t byte_offset) :
    mode(mode),
    type(type),
    vertex_count(vertex_count),
    byte_offset(byte_offset){
}

ArrayAccessor::~ArrayAccessor(){
}

void ArrayAccessor::draw(){
    glDrawElements(static_cast<GLenum>(mode), vertex_count,
                   static_cast<GLenum>(type), (void*)byte_offset);
}