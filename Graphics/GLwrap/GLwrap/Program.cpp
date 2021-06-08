#include "GLwrap/Program.h"

#include <stdexcept>

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

void Program::use(){
    glUseProgram(__id);
}

GLuint Program::getUniformLoc(const std::string &name){
    auto loc = glGetUniformLocation(__id, name.c_str());
    if (loc < 0){
        std::string pos = typeid(this).name();
        pos += ".";
        pos += __func__;
        throw std::invalid_argument(pos + ": can not get " + name);
    }

    return glGetUniformLocation(__id, name.c_str());
}

void Program::setUniformMat4f(const std::string &name, const float mat[16]){
    auto loc = getUniformLoc(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}