#pragma once

#include "glad/gl.h"

#include "GLwrap/Types.h"

namespace GLwrap {

class Tex2D {
public:
    Tex2D(GLsizei width, GLsizei height, Tex2DInternalFormat format,
          Tex2DPixelFormat usage, Tex2DPixelType pixel_type);
    virtual ~Tex2D();

    void bind() const;
    void unbind() const;
    void enable(GLuint index) const;

    void write(const void *data,  
               GLsizei x, GLsizei y,
               GLsizei width, GLsizei height);


    void setWrapS(Tex2DWrap wrap);
    Tex2DWrap getWrapS() const;

    void setWrapT(Tex2DWrap wrap);
    Tex2DWrap getWrapT() const;

    void setMinFilter(Tex2DFilter filter);
    Tex2DFilter getMinFilter() const;

    void setMagFilter(Tex2DFilter filter);
    Tex2DFilter getMagFilter() const;

    const GLuint id;

    const GLsizei width;
    const GLsizei height;
    const Tex2DInternalFormat format; 
    const Tex2DPixelFormat pixel_format;
    const Tex2DPixelType pixel_type;
    
private:
    static GLuint _newId();

    Tex2DWrap _wrap_s;
    Tex2DWrap _wrap_t;

    Tex2DFilter _min_filter;
    Tex2DFilter _mag_filter;
};

}