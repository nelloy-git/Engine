#include "GLSL/Shader.h"

using namespace Graphics::GLSL;

Shader::Shader(const std::string& source){
    auto pId = const_cast<GLuint*>(&id);
    glCreateShader(1, pId);
    glShaderSource(id, 1, source.c_str(), nullptr);
    glCompileShader(id)
}

Shader::~Shader(){
    glDeleteShader(id);
}