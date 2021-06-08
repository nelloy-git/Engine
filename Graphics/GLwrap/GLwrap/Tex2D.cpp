#include "GLwrap/Tex2D.h"

using namespace GLwrap;

const std::vector<std::pair<Tex2DParamInt, GLuint>> Tex2D::__default_uint_params = {
    {Tex2DParamInt::WRAP_S, GL_REPEAT},
    {Tex2DParamInt::WRAP_T, GL_REPEAT},
    {Tex2DParamInt::MIN_FILTER, GL_LINEAR},
    {Tex2DParamInt::MAG_FILTER, GL_LINEAR},
};

Tex2D::Tex2D(){
    glGenTextures(1, &__id);
}

Tex2D::~Tex2D(){
    glDeleteTextures(1, &__id);
}

GLuint Tex2D::id(){
    return __id;
}

void Tex2D::free(){
    if (__loaded){
        glDeleteTextures(1, &__id);
        glGenTextures(1, &__id);
        __loaded = false;
    }
}

void Tex2D::bind(){
    glBindTexture(GL_TEXTURE_2D, __id);
}

void Tex2D::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tex2D::setActive(GLuint index){
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, __id);
}

void Tex2D::load(const void *data, GLsizei width, GLsizei height,
               Tex2DinternalFormat in_fmt, Tex2Dformat usage, Tex2DpixelType pixel,
               const std::vector<std::pair<Tex2DParamInt, GLuint>> &uint_params){

    free();

    glBindTexture(GL_TEXTURE_2D, __id);
    for (auto param : uint_params){
        glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(param.first), param.second);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(in_fmt), width, height, 0,
                 static_cast<GLenum>(usage), static_cast<GLenum>(pixel), data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    __loaded = true;
}