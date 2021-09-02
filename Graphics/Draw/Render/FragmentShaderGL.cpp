#include "Draw/Render/FragmentShaderGL.hpp"

using namespace Graphics::Render;

FragmentShaderGL::FragmentShaderGL(const std::string &source){
    gl = std::make_unique<GLwrap::Shader>(GLwrap::ShaderType::Fragment, source);
}

FragmentShaderGL::~FragmentShaderGL(){
}

const std::string &FragmentShaderGL::_getSource(){
    static std::string source = 
R"(
#version 420 core

in vec3 baseColor;
in vec2 outTexCoord_0;
in vec2 outTexCoord_1;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
   gl_FragColor = texture(texture0, outTexCoord_0) * texture(texture1, outTexCoord_1) * vec4(baseColor, 0);
}
)";
    return source;
}