#include "GLwrap/Shader.h"

using namespace Graphics::GLwrap;

Shader::Shader(ShaderType type, const std::string& source){
    auto pId = const_cast<GLuint*>(&id);
    *pId = glCreateShader(static_cast<GLenum>(type));

    auto c_str = source.c_str();
    glShaderSource(id, 1, &c_str, nullptr);
    glCompileShader(id);
}

Shader::~Shader(){
    glDeleteShader(id);
}