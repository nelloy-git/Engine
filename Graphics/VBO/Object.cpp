#include "VBO/Object.h"

using namespace Graphics::VBO;

Object::Object(BufferType type, size_t size, UsageType usage) :
    id(0),
    type(type),
    size(size),
    usage(usage){

    auto pId = const_cast<GLuint*>(&id);
    glGenBuffers(1, pId);

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferData(static_cast<GLenum>(type), size, nullptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

Object::~Object(){
    glDeleteBuffers(1, &id);
}

void Object::load(int bytes_offset, size_t size, const void* data){
    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferSubData(static_cast<GLenum>(type), bytes_offset, size, data);
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Object::bind() const {
    glBindBuffer(static_cast<GLenum>(type), id);
}

void Object::unbind() const {
    glBindBuffer(static_cast<GLenum>(type), 0);
}