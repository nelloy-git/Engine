#pragma once

#include <string>
#include <vector>

#include "GLwrap/Array.h"
#include "GLwrap/BufferTyped.h"
#include "GLwrap/BufferAccessor.h"
#include "GLwrap/Shader.h"

#include "Draw/Render/ShaderIFaces.hpp"

namespace Graphics::Render {

template<typename T>
class ShaderInputGL : public ShaderInput {
public:
    // nullptr for default shader.
    ShaderInputGL(const std::string *src = nullptr){
        ShaderInput(), gl(src)
    };
    virtual ~ShaderInputGL(){};

    using Input = T;
    // There is only 16 layouts for vec4 vertex attributes. 
    static_assert(sizeof(T) <= 16 * 4 * sizeof(float));

    virtual GLwrap::Array *createArray(const std::vector<T> &data) = 0;

    const GLwrap::Shader gl;
};

}