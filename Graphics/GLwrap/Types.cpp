#include "GLwrap/Types.h"

size_t Graphics::GLwrap::getShaderDataTypeSize(ShaderDataType type){
    switch (type){
    case ShaderDataType::Float:
        return sizeof(GLfloat);

    case ShaderDataType::UInt:
        return sizeof(GLuint);
    
    default:
        throw std::invalid_argument("Unknown ShaderDataType");
    }
}