#include "GLwrap/Program.h"

#include <stdexcept>

#include "glad/gl.h"

using namespace GLwrap;

Program *Program::__active_program = nullptr;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach){
    __id = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(__id, shader->id());
    }
    glLinkProgram(__id);
}

Program::~Program(){
    if (__id != 0){
        glDeleteProgram(__id);
    }
}

Program *Program::getActive(){
    return __active_program;
}

GLuint Program::id(){
    return __id;
}

GLuint Program::id() const {
    return __id;
}

void Program::use(){
    glUseProgram(__id);
    __active_program = this;
}

bool getUniformLoc(GLuint prog_id, const std::string &name, GLuint *loc){
    *loc = glGetUniformLocation(prog_id, name.c_str());
    if (loc < 0){
        return false;
    }
    return true;
}

bool Program::setUniformVec4f(const std::string &name, const float vec[4]){
    GLuint loc;
    if (!getUniformLoc(__id, name, &loc)){
        return false;
    }
    glUniform4fv(loc, 1, vec);
    return true;
}

bool Program::setUniformMat4f(const std::string &name, const float mat[16]){
    GLuint loc;
    if (!getUniformLoc(__id, name, &loc)){
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    return true;
}