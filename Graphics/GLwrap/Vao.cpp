#include "GLwrap/Vao.h"

using namespace Graphics::GLwrap;

VAO::VAO() :
    id(0){
    auto pId = const_cast<GLuint*>(&id);
    glGenVertexArrays(1, pId);
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &id);
}

void VAO::attrib(std::vector<VAOdata> &list){
    // glBindVertexArray(id);

    // int i = 0;
    // for (auto data : list){
    //     data.buff->bind();
    //     auto step = static_cast<GLuint>(data.size) * getShaderDataTypeSize(data.type);
    //     printf("%d\n", step);
    //     glVertexAttribPointer(i++, static_cast<GLuint>(data.size), static_cast<GLenum>(data.type), GL_FALSE, step, 0);
    //     glEnableVertexAttribArray(i);
    //     data.buff->unbind();
    // }

    // glBindVertexArray(0);
}

void VAO::bind(){
    glBindVertexArray(id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}