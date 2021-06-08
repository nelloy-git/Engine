#include "GLwrap/Vao.h"

using namespace GLwrap;

VAO::VAO() :
    id(0){
    auto pId = const_cast<GLuint*>(&id);
    glGenVertexArrays(1, pId);
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &id);
}

void VAO::bind(){
    glBindVertexArray(id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}