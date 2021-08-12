#include "Draw/Render/GLwrap/Default/ShaderImputGLDefault.hpp"

using namespace Graphics::Render;

ShaderInputGLDefault::ShaderInputGLDefault() :
    ShaderInputGL<ShaderInputGLDefaultInput>(&_getSources()){
}

ShaderInputGLDefault::~ShaderInputGLDefault(){
}

const std::string &ShaderInputGLDefault::_getSources(){
    static std::string src = 
        #include "Draw/Render/GLwrap/input.vert.glsl"
    ;
    return src;
}