#include "Draw/Render/GLwrap/Default/ShaderFragmentGLDefault.hpp"

using namespace Graphics::Render;

ShaderFragmentGLDefault::ShaderFragmentGLDefault() :
    ShaderFragmentGL(_getSources()){
}

ShaderFragmentGLDefault::~ShaderFragmentGLDefault(){
}

const std::string &ShaderFragmentGLDefault::_getSources(){
    static std::string src =
        #include "Draw/Render/GLwrap/Default/default.frag.glsl"
    ;
    return src;
}