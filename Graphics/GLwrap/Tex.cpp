#include "GLwrap/Tex.h"

using namespace Graphics::GLwrap;

const std::vector<std::pair<Tex2DParamInt, GLuint>> Tex::__default_uint_params = {
    {Tex2DParamInt::WRAP_S, GL_REPEAT},
    {Tex2DParamInt::WRAP_T, GL_REPEAT},
    {Tex2DParamInt::MIN_FILTER, GL_LINEAR},
    {Tex2DParamInt::MAG_FILTER, GL_LINEAR},
};

Tex::Tex() :
    id(0){
    
    auto pId = const_cast<GLuint*>(&id);
    glGenTextures(1, pId);
}

Tex::~Tex(){
    glDeleteTextures(1, &id);
}

void Tex::bind(){
    glBindTexture(GL_TEXTURE_2D, id);
}

void Tex::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tex::load(GLsizei width, GLsizei height, const void *data,
               const std::vector<std::pair<Tex2DParamInt, GLuint>> &uint_params){

    glBindTexture(GL_TEXTURE_2D, id);
    for (auto param : uint_params){
        glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(param.first), param.second);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}