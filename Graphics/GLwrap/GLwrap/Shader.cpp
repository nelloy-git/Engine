#include "GLwrap/Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <stdexcept>

using namespace GLwrap;

Shader::Shader(ShaderType type, const std::string& path){
    __id = glCreateShader(static_cast<GLenum>(type));

    auto code = __loadFromFile(path);
    auto c_code = code.c_str();

    glShaderSource(__id, 1, &c_code, nullptr);
    glCompileShader(__id);

    auto res = GL_FALSE;
    glGetShaderiv(__id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE){
        char log[4096];
        GLsizei msglen;
        glGetShaderInfoLog(__id, 4096, &msglen, log);
        std::string msg(typeid(this).name());
        throw std::invalid_argument(msg + "(" + path + "): " + log);
    }
}

Shader::~Shader(){
    glDeleteShader(__id);
}

GLuint Shader::id(){
    return __id;
}

std::string Shader::__loadFromFile(const std::string &path){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string code;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(path);
        std::stringstream str_stream;

        std::string line;
        while(!file.eof()){
	        std::getline(file, line); // Saves the line in STRING.
	        code += line + "\n"; 
        }
        file.close();
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return code;
}

size_t GLwrap::getDataTypeSize(ComponentType type){
    switch (type){

    case ComponentType::Float:
        return sizeof(GLfloat);

    case ComponentType::UInt:
        return sizeof(GLuint);
    
    default:
        throw std::invalid_argument("Unknown ShaderDataType");
    }
}