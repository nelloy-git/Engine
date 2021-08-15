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

    BufferArray(const Buffer &data,
                const std::unordered_map<Layout, const BufferAccessor *> &accessors);

    template<typename T>
    BufferArray(const Buffer &data,
                const std::unordered_map<Layout, const BufferAccessor *> &accessors,
                const BufferTyped<T> &indices) :
        id(_newId()),
        indexed(true),
        _indices_type(fromType<T>()),
        _indices_count(indices.size){
        static_assert(_indices_type == ElementType::UByte
                      || _indices_type == ElementType::UShort
                      || _indices_type == ElementType::UInt,
                      "Wrong indices data type");
        _bindBuffers(data, accessors, {&indices});
    }

    using BufferPair = std::pair<const GLwrap::Buffer *,
                                 const GLwrap::BufferAccessor *>;

    BufferArray(const std::unordered_map<Layout, BufferPair> &layouts);

    template<typename T>
    BufferArray(const std::unordered_map<Layout, BufferPair> &layouts,
                const BufferTyped<T> &indices) :
        id(_newId()),
        indexed(true),
        _indices_type(fromType<T>()),
        _indices_count(indices.size){
        static_assert(_indices_type == ElementType::UByte
                      || _indices_type == ElementType::UShort
                      || _indices_type == ElementType::UInt,
                      "Wrong indices data type");
        _bindBuffers(layouts, {&indices});
    }

    virtual ~BufferArray();

    static GLint max_layouts();

    const GLuint id;
    const bool indexed;
    
    void bind() const;
    void unbind() const;

    void draw() const;
    void drawArrays(DrawMode mode, GLuint first, GLuint count) const;
    void drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset) const;

private:
    static GLuint _newId();

    void _bindBuffers(const Buffer &data,
                      const std::unordered_map<Layout, const BufferAccessor *> &accessors,
                      const std::optional<const Buffer *> indices);

    void _bindBuffers(const std::unordered_map<Layout, BufferPair> &layouts,
                      const std::optional<const Buffer *> indices);

    const std::optional<ElementType> _indices_type;
    const GLuint _indices_count;

};

}