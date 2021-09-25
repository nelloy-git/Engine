#include "Graphics/Render/Easy/FShader.hpp"

using namespace Graphics::Render::Easy;

using Vertex = FShader::Vertex;

FShader::FShader()
    : Base::FShader(_getSource()){
}

const std::string &FShader::_getSource(){
    static const auto src = _createSourceAll();
    return src;
}

std::string FShader::_createSourceAll(){
    std::string src = R"(
#version 450 core

in vec4 baseColor;
in vec2 outTexCoord[)"
 + std::to_string(sizeof(FShader::Vertex::tex_coord) / sizeof(FShader::Vertex::tex_coord[0])) +
R"(];

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
    gl_FragColor = vec4(1, 1, 1, 1);
    // gl_FragColor = baseColor;
    // gl_FragColor = texture(texture0, outTexCoord_0) * texture(texture1, outTexCoord_1) * baseColor;
}
)";

    std::cout << "FShader:\n" << src.c_str();

    return src;
}