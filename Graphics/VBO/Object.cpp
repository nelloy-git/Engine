#include "VBO/Object.h"

using namespace Graphics::VBO;

Object::Object(DataType type) :
    id(0),
    type(type){

    auto pId = const_cast<GLuint*>(&id);
    glGenBuffers(1, pId);
}

Object::~Object(){
    glDeleteBuffers(1, &id);
}

void Object::load(const size_t size, const void* ptr, UsageType usage){
    __size = size;
    __ptr = ptr;
    __usage = usage;

    glBindBuffer(static_cast<GLenum>(type), id);
    glBufferData(static_cast<GLenum>(type), __size, ptr, static_cast<GLenum>(usage));
    glBindBuffer(static_cast<GLenum>(type), 0);
}

void Object::bind(){
    glBindBuffer(static_cast<GLenum>(type), id);
}

void Object::unbind(){
    glBindBuffer(static_cast<GLenum>(type), 0);
}

int Object::size(){
    return __size;
}

const void* Object::ptr(){
    return __ptr;
}

UsageType Object::usage(){
    return __usage;
}