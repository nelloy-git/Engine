#include "GLwrap/Tex2D.h"

using namespace GLwrap;

Tex2D::Tex2D(GLsizei width, GLsizei height, Tex2DInternalFormat format,
             Tex2DPixelFormat pixel_format, Tex2DPixelType pixel_type) :
    id(_newId()),
    width(width),
    height(height),
    format(format),
    pixel_format(pixel_format),
    pixel_type(pixel_type),
    wrap_s(this, &Tex2D::_getWrapS, &Tex2D::_setWrapS),
    wrap_t(this, &Tex2D::_getWrapT, &Tex2D::_setWrapT),
    min_filter(this, &Tex2D::_getMinFilter, &Tex2D::_setMinFilter),
    mag_filter(this, &Tex2D::_getMagFilter, &Tex2D::_setMagFilter){

    wrap_s = Tex2DWrap::Repeat;
    wrap_t = Tex2DWrap::Repeat;
    min_filter = Tex2DFilter::Linear;
    mag_filter = Tex2DFilter::Linear;

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format),
                 width, height, 0, static_cast<GLenum>(pixel_format),
                 static_cast<GLenum>(pixel_type), nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Tex2D::~Tex2D(){
    glDeleteTextures(1, &id);
}

void Tex2D::bind(){
    glBindTexture(GL_TEXTURE_2D, id);
}

void Tex2D::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tex2D::setActive(GLuint index){
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Tex2D::write(const void *data,  
                  GLsizei x, GLsizei y,
                  GLsizei width, GLsizei height){

    glBindTexture(GL_TEXTURE_2D, id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
                    static_cast<GLenum>(format), static_cast<GLenum>(pixel_type), data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Tex2D::_newId(){
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

const Tex2DWrap &Tex2D::_getWrapS(){
    return _wrap_s;
}

void Tex2D::_setWrapS(const Tex2DWrap &wrap){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
    glBindTexture(GL_TEXTURE_2D, 0);
    _wrap_s = wrap;
}

const Tex2DWrap &Tex2D::_getWrapT(){
    return _wrap_t;
}

void Tex2D::_setWrapT(const Tex2DWrap &wrap){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
    glBindTexture(GL_TEXTURE_2D, 0);
    _wrap_t = wrap;
}

const Tex2DFilter &Tex2D::_getMinFilter(){
    return _min_filter;
}

void Tex2D::_setMinFilter(const Tex2DFilter &filter){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
    glBindTexture(GL_TEXTURE_2D, 0);
    _min_filter = filter;
}

const Tex2DFilter &Tex2D::_getMagFilter(){
    return _mag_filter;
}

void Tex2D::_setMagFilter(const Tex2DFilter &filter){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
    glBindTexture(GL_TEXTURE_2D, 0);
    _mag_filter = filter;
}