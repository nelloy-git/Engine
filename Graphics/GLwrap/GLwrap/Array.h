#pragma once

#include <any>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "glad/gl.h"

#include "GLwrap/BufferAccessor.h"
#include "GLwrap/BufferTyped.h"

namespace GLwrap {

class BufferArray {
public:
    using Layout = unsigned int;

    template<class T, class K = unsigned int>
    BufferArray(const BufferTyped<T> *data,
                const std::unordered_map<Layout, const BufferAccessor *> *accessors,
                const BufferTyped<K> *indices = nullptr) :
        id(_newId()),
        indexed(indices != nullptr),
        _indices_type(fromType<K>()),
        _vertex_count(indices ? indices->size : data->size){
        static_assert(fromType<K>() == ElementType::UByte
                      || fromType<K>() == ElementType::UShort
                      || fromType<K>() == ElementType::UInt,
                      "Wrong indices data type");
        _bindBuffers(data, accessors, {indices});
    }

    virtual ~BufferArray();

    static GLint max_layouts();

    const GLuint id;
    const bool indexed;
    
    void bind() const;
    void unbind() const;

    void draw(DrawMode mode) const;

private:
    static GLuint _newId();

    void _bindBuffers(const Buffer *data,
                      const std::unordered_map<Layout, const BufferAccessor *> *accessors,
                      const std::optional<const Buffer *> indices);

    const std::optional<ElementType> _indices_type;
    const GLuint _vertex_count;

};

}