#include "GLwrap/Program.h"

#include <stdexcept>

#include "glad/gl.h"

using namespace GLwrap;

Program *Program::_active_program = nullptr;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach){
    _id = glCreateProgram();

    for (auto shader : attach){
        glAttachShader(_id, shader->id());
    }
    glLinkProgram(_id);
}

Program::~Program(){
    if (_id != 0){
        glDeleteProgram(_id);
    }
}

Program *Program::getActive(){
    return _active_program;
}

GLuint Program::id(){
    return _id;
}

GLuint Program::id() const {
    return _id;
}

void Program::use(){
    glUseProgram(_id);
    _active_program = this;
}

GLuint Program::getAttribLoc(const std::string &name){
    return glGetAttribLocation(_id, name.c_str());
}

GLuint Program::getAttribLoc(const std::string &name) const {
    return glGetAttribLocation(_id, name.c_str());
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
    if (!getUniformLoc(_id, name, &loc)){
        return false;
    }
    glUniform4fv(loc, 1, vec);
    return true;
}

bool Program::setUniformMat4f(const std::string &name, const float mat[16]){
    GLuint loc;
    if (!getUniformLoc(_id, name, &loc)){
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    return true;
}