#include "GLSL/Program.h"

using namespace Graphics::GLSL;

Program::Program(std::vector<Shader*>& attach){
    auto pId = const_cast<GLuint*>(&id);
    *pId = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);
}

Shader::~Shader(){
    glDeleteShader(id);
}