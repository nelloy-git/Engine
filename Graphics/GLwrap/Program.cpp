#include "GLwrap/Program.h"

using namespace GLwrap;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach){
    __id = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(__id, shader->id());
    }
    glLinkProgram(__id);
}

Program::~Program(){
    glDeleteProgram(__id);
}

GLuint Program::id(){
    return __id;
}