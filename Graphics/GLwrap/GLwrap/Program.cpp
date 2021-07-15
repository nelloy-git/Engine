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

