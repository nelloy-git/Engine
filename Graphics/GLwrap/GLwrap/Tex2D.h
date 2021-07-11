#pragma once

#include <vector>
#include <utility>

#include "glad/gl.h"

#include "Property.h"
#include "GLwrap/Types.h"

namespace GLwrap {

class Tex2D {
public:
    Tex2D(GLsizei width, GLsizei height, Tex2DInternalFormat format,
          Tex2DPixelFormat usage, Tex2DPixelType pixel_type);
    virtual ~Tex2D();

    GLuint id();
    void bind();
    void unbind();
    void setActive(GLuint index);

    void write(const void *data,  
               GLsizei x, GLsizei y,
               GLsizei width, GLsizei height);

    const GLsizei width;
    const GLsizei height;
    const Tex2DInternalFormat format; 
    const Tex2DPixelFormat pixel_format;
    const Tex2DPixelType pixel_type;

    Property<Tex2DWrap, Tex2D> wrap_s;
    Property<Tex2DWrap, Tex2D> wrap_t;

    Property<Tex2DFilter, Tex2D> min_filter;
    Property<Tex2DFilter, Tex2D> mag_filter;
    
private:
    GLuint _id;

    Tex2DWrap _wrap_s;
    const Tex2DWrap &_getWrapS();
    void _setWrapS(const Tex2DWrap &wrap);

    Tex2DWrap _wrap_t;
    const Tex2DWrap &_getWrapT();
    void _setWrapT(const Tex2DWrap &wrap);

    Tex2DFilter _min_filter;
    const Tex2DFilter &_getMinFilter();
    void _setMinFilter(const Tex2DFilter &filter);

    Tex2DFilter _mag_filter;
    const Tex2DFilter &_getMagFilter();
    void _setMagFilter(const Tex2DFilter &filter);
};

}