#include "GLwrap/Program.h"

#include <stdexcept>

#include "glad/gl.h"

using namespace GLwrap;

Program::Program(const std::vector<const Shader *> &attach) :
    id(glCreateProgram()){

    for (auto shader : attach){
        if (!shader) continue;
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);

    auto res = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &res);
    if (res == GL_FALSE){
        char msg[4096];
        GLsizei msglen;
        glGetProgramInfoLog(id, 4096, &msglen, msg);
        throw std::invalid_argument("GLwrap::Program: " + std::string(msg));
    }
}

Program::~Program(){
    glDeleteProgram(id);
}

void Program::use() const{
    glUseProgram(id);
}

GLuint Program::getAttribLoc(const std::string &name){
    auto iter = _attributes.find(name);
    if (iter == _attributes.end()){
        _attributes[name] = glGetAttribLocation(id, name.c_str());
        iter = _attributes.find(name);
    }

    return iter->second;
}

GLuint Program::getUniformLoc(const std::string &name){
    auto iter = _uniforms.find(name);
    if (iter == _uniforms.end()){
        _uniforms[name] = glGetUniformLocation(id, name.c_str());
        iter = _uniforms.find(name);
    }

    return iter->second;
}

bool Program::setUniform1vf(const std::string &name, const float val){
    GLuint loc = getUniformLoc(name);
    if (loc < 0){
        return false;
    }
    glUniform1f(loc, val);
    return true;
}

bool Program::setUniformFloatArray(const std::string &name, const float *ptr, size_t size){
    GLuint loc = getUniformLoc(name);
    if (loc < 0){
        return false;
    }
    glUniform1fv(loc, size, ptr);
    return true;
}

bool Program::setUniform1vi(const std::string &name, const int val){
    GLuint loc = getUniformLoc(name);
    if (loc < 0){
        return false;
    }
    glUniform1i(loc, val);
    return true;
}

bool Program::setUniformVec4f(const std::string &name, const float vec[4]){
    GLuint loc = getUniformLoc(name);
    if (loc < 0){
        return false;
    }
    glUniform4fv(loc, 1, vec);
    return true;
}

bool Program::setUniformMat4f(const std::string &name, const float mat[16]){
    GLuint loc = getUniformLoc(name);
    if (loc < 0){
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    return true;
}

