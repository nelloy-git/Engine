#include "GLwrap/Program.h"

using namespace Graphics::GLwrap;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach){
    auto pId = const_cast<GLuint*>(&id);
    *pId = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);
}

Program::~Program(){
    glDeleteProgram(id);
}