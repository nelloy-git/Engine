#pragma once

#include "glad/gl.h"

#include "glw/Types.hpp"

namespace glw {

class Tex2D {
public:
    Tex2D() :
        id(_newId()){
    };

    virtual ~Tex2D(){
        glDeleteTextures(1, &id);
    }

    inline void bind() const {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    inline void enableAt(GLuint index) const {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    inline void write(const void *data,  
               GLsizei x, GLsizei y,
               GLsizei width, GLsizei height){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
                        gl(_internal_format), gl(_pixel_data_type), data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    inline void resize(GLsizei width, GLsizei height,
                       Tex2DInternalFormat internal, Tex2DPixelDataFormat pix_fmt, Tex2DPixelDataType pix_type){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl(_wrap_s));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl(_wrap_t));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl(_min_filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl(_mag_filter));
        glTexImage2D(GL_TEXTURE_2D, 0, gl(_internal_format), width, height, 0, gl(pix_fmt), gl(pix_type), nullptr);

        _width = width;
        _height = height;
        _internal_format = internal;
        _pixel_data_format = pix_fmt;
        _pixel_data_type = pix_type;
    }

    inline void setWrapS(Tex2DWrap wrap){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl(wrap));
        _wrap_s = wrap;
    };

    inline Tex2DWrap getWrapS() const {
        return _wrap_s;
    };

    inline void setWrapT(Tex2DWrap wrap){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl(wrap));
        _wrap_t = wrap;
    }

    inline Tex2DWrap getWrapT() const {
        return _wrap_t;
    }

    inline void setMinFilter(Tex2DFilter filter){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl(filter));
        _min_filter = filter;
    }

    inline Tex2DFilter getMinFilter() const {
        return _min_filter;
    }

    inline void setMagFilter(Tex2DFilter filter){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl(filter));
        glBindTexture(GL_TEXTURE_2D, 0);
        _mag_filter = filter;
    }

    inline Tex2DFilter getMagFilter() const {
        return _mag_filter;
    }

    const GLuint id;
    
private:
    static GLuint _newId(){
        GLuint id;
        glGenTextures(1, &id);
        return id;
    }

    GLsizei _width;
    GLsizei _height;
    Tex2DInternalFormat _internal_format; 
    Tex2DPixelDataFormat _pixel_data_format;
    Tex2DPixelDataType _pixel_data_type;

    Tex2DWrap _wrap_s = Tex2DWrap::Repeat;
    Tex2DWrap _wrap_t = Tex2DWrap::Repeat;
    Tex2DFilter _min_filter = Tex2DFilter::Linear;
    Tex2DFilter _mag_filter = Tex2DFilter::Linear;
};

}