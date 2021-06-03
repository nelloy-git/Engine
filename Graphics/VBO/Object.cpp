#include "VBO/Object.h"

using namespace Graphics::VBO;

// Object::Object(DataType type) :
//     type(type){

//     auto pId = const_cast<GLuint*>(&id);
//     glGenBuffers(1, pId);
// }

// Object::~Object(){
//     glDeleteBuffers(1, &id);
// }

// void Object::bind(){
//     glBindBuffer(static_cast<GLenum>(type), id);
// }

// void Object::unbind(){
//     glBindBuffer(static_cast<GLenum>(type), 0);
// }