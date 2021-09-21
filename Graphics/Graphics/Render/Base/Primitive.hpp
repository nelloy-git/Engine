#pragma once

#include <iostream>
#include <vector>

#include "GLwrap/Array.h"
#include "GLwrap/BufferTyped.h"
#include "GLwrap/Tex2D.h"

#include "Graphics/Render/Base/Vertex.hpp"

namespace Graphics::Render::Base {

template<VertexStruct S>
using Data = GLwrap::BufferTyped<Vertex<S>>;
using Indices = GLwrap::BufferTyped<unsigned int>;
using Object = GLwrap::BufferArray;
using Texture = GLwrap::Tex2D;

template<VertexStruct S>
class Primitive {
public:
    using Accessors = Object::Accessors;

    explicit Primitive(const std::vector<Vertex<S>> &data,
                       const std::vector<unsigned int> *indices = nullptr) :
        _gl_buffer(new Data<S>(GLwrap::BufferType::Array, data)),
        _gl_indices(indices ? new Indices(GLwrap::BufferType::IndexArray, *indices) : nullptr),
        _gl_object(new Object(*(_gl_buffer.get()), _getAccessors(), _gl_indices.get())){
    };
    Primitive(const Primitive &) = delete;
    Primitive(Primitive &&prim) = default;
    virtual ~Primitive() = default;

    inline void draw() const {
        _gl_object->draw(gl_draw_mode);
    }

    GLwrap::DrawMode gl_draw_mode = GLwrap::DrawMode::Triangles;

protected:
    std::unique_ptr<Data<S>> _gl_buffer;
    std::unique_ptr<Indices> _gl_indices;
    std::unique_ptr<Object> _gl_object;


protected:
    static const Accessors &_getAccessors(){
        static const auto acc = _createAccessors();
        return acc;
    }

    static Accessors _createAccessors(){
        const int vec4_count = std::ceil((float)(sizeof(Vertex<S>) / sizeof(float)) / 4.0);
        const int vec4_bytes = 4 * sizeof(float);

        Primitive::Accessors acc;

        for (int i = 0; i < vec4_count; ++i){
            using namespace GLwrap;
            acc[i] = new BufferAccessor(ElementStruct::Vec4,
                                        ElementType::Float,
                                        false,
                                        sizeof(Vertex<S>),
                                        i * vec4_bytes);
        }

        return acc;
    }
};

}