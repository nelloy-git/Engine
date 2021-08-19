#pragma once

#include "GLwrap/Array.h"

namespace Graphics::Render {

template<typename T>
class PrimitiveGL {
friend class RendererGL;
public:
    virtual ~PrimitiveGL(){};

    GLwrap::BufferArray gl;

private:
    PrimitiveGL(const GLwrap::BufferTyped<T> &data,
                const std::unordered_map<GLwrap::BufferArray::Layout, const GLwrap::BufferAccessor *> &accessors) :
        gl(data, accessors){
    };

    PrimitiveGL(const GLwrap::BufferTyped<T> &data,
                const std::unordered_map<GLwrap::BufferArray::Layout, const GLwrap::BufferAccessor *> &accessors,
                const GLwrap::BufferTyped<unsigned int> &indices) :
        gl(data, accessors, indices){
    };

};

}