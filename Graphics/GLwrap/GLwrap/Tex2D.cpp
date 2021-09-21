#include "GLwrap/Tex2D.h"

using namespace GLwrap;

Tex2D::Tex2D(GLsizei width, GLsizei height, Tex2DInternalFormat format,
             Tex2DPixelFormat pixel_format, Tex2DPixelType pixel_type) :
    id(_newId()),
    width(width),
    height(height),
    format(format),
    pixel_format(pixel_format),
    pixel_type(pixel_type){

    setWrapS(Tex2DWrap::Repeat);
    setWrapT(Tex2DWrap::Repeat);
    setMinFilter(Tex2DFilter::Linear);
    setMagFilter(Tex2DFilter::Linear);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format),
                 width, height, 0, static_cast<GLenum>(pixel_format),
                 static_cast<GLenum>(pixel_type), nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Tex2D::~Tex2D(){
    glDeleteTextures(1, &id);
}

void Tex2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Tex2D::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tex2D::enable(GLuint index) const {
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

Tex2DWrap Tex2D::getWrapS() const {
    return _wrap_s;
}

void Tex2D::setWrapS(Tex2DWrap wrap){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
    glBindTexture(GL_TEXTURE_2D, 0);
    _wrap_s = wrap;
}

Tex2DWrap Tex2D::getWrapT() const {
    return _wrap_t;
}

void Tex2D::setWrapT(Tex2DWrap wrap){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
    glBindTexture(GL_TEXTURE_2D, 0);
    _wrap_t = wrap;
}

Tex2DFilter Tex2D::getMinFilter() const {
    return _min_filter;
}

void Tex2D::setMinFilter(Tex2DFilter filter){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
    glBindTexture(GL_TEXTURE_2D, 0);
    _min_filter = filter;
}

Tex2DFilter Tex2D::getMagFilter() const {
    return _mag_filter;
}

void Tex2D::setMagFilter(Tex2DFilter filter){
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
    glBindTexture(GL_TEXTURE_2D, 0);
    _mag_filter = filter;
}