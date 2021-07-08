#include "GLwrap/Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Log.h"

using namespace GLwrap;

Shader::Shader(ShaderType type, const std::string& code){
    __id = glCreateShader(static_cast<GLenum>(type));

    auto c_code = code.c_str();

    glShaderSource(__id, 1, &c_code, nullptr);
    glCompileShader(__id);

    auto res = GL_FALSE;
    glGetShaderiv(__id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE){
        char msg[4096];
        GLsizei msglen;
        glGetShaderInfoLog(__id, 4096, &msglen, msg);
        throw std::invalid_argument(msg);
    }
}

std::shared_ptr<Shader> Shader::fromFile(ShaderType type, const std::string& path){
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
    } catch(std::ifstream::failure e){
        // auto s = __;
        LOG(WRN) << "can not read file";
        return nullptr;
    }

    std::shared_ptr<Shader> shader;
    try {
        shader = std::make_shared<Shader>(type, code);
    } catch (std::invalid_argument e){
        LOG(ERR) << "Can not load shader from file: " << path << "\n\t" << e.what();
        return nullptr;
    }

    return shader;
}

Shader::~Shader(){
    glDeleteShader(__id);
}

GLuint Shader::id(){
    return __id;
}

size_t GLwrap::getDataTypeSize(ElementType type){
    switch (type){

    case ElementType::Float:
        return sizeof(GLfloat);

    case ElementType::UInt:
        return sizeof(GLuint);
    
    default:
        throw std::invalid_argument("Unknown ShaderDataType");
    }
}