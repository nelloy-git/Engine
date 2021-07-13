#include "GLwrap/Program.h"

#include <stdexcept>

#include "glad/gl.h"

using namespace GLwrap;

Program::Program(const std::vector<std::shared_ptr<Shader>>& attach) :
    id(glCreateProgram()){

    for (auto shader : attach){
        glAttachShader(id, shader->id());
    }
    glLinkProgram(id);
}

Program::~Program(){
    glDeleteProgram(id);
}

void Program::use() const{
    glUseProgram(id);
}

GLuint Program::getAttribLoc(const std::string &name) const {
    return glGetAttribLocation(id, name.c_str());
}

bool getUniformLoc(GLuint progid, const std::string &name, GLuint *loc){
    *loc = glGetUniformLocation(progid, name.c_str());
    if (loc < 0){
        return false;
    }
    return true;
}

bool Program::setUniformVec4f(const std::string &name, const float vec[4]){
    GLuint loc;
    if (!getUniformLoc(id, name, &loc)){
        return false;
    }
    glUniform4fv(loc, 1, vec);
    return true;
}

bool Program::setUniformMat4f(const std::string &name, const float mat[16]){
    GLuint loc;
    if (!getUniformLoc(id, name, &loc)){
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    return true;
}

