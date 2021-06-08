#include "GLwrap/Shader.h"

#include <stdexcept>

using namespace GLwrap;

Shader::Shader(ShaderType type, const std::string& source){
    __id = glCreateShader(static_cast<GLenum>(type));

    auto c_str = source.c_str();
    glShaderSource(__id, 1, &c_str, nullptr);
    glCompileShader(__id);
}

Shader::~Shader(){
    glDeleteShader(__id);
}

GLuint Shader::id(){
    return __id;
}

size_t Shader::getDataTypeSize(ShaderDataType type){
    switch (type){

    case ShaderDataType::Float:
        return sizeof(GLfloat);

    case ShaderDataType::UInt:
        return sizeof(GLuint);
    
    default:
        throw std::invalid_argument("Unknown ShaderDataType");
    }
}