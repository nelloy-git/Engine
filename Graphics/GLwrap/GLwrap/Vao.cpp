#include "GLwrap/Vao.h"

using namespace GLwrap;

VAO::VAO(){
    glGenVertexArrays(1, &__id);
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &__id);
}

void VAO::bind(){
    glBindVertexArray(__id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}