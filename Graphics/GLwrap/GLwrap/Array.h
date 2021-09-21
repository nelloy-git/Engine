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
    using Accessors = std::unordered_map<Layout, const BufferAccessor *>;

    template<class T, class K = unsigned int>
    BufferArray(const BufferTyped<T> &data,
                const Accessors &accessors,
                const BufferTyped<K> *indices = nullptr) :
        id(_newId()),
        indexed(indices != nullptr),
        _indices_type(fromType<K>()),
        _vertex_count(indices ? indices->size : data.size){
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
    
    inline void bind() const{
        glBindVertexArray(id);
    };

    inline void unbind() const {
        glBindVertexArray(0);
    };

    inline void draw(DrawMode mode) const {
        glBindVertexArray(id);
        if (indexed){
            glDrawElements(static_cast<GLenum>(mode),
                           _vertex_count,
                           static_cast<GLenum>(_indices_type.value()),
                           (void*)0);
        } else {
            glDrawArrays(static_cast<GLenum>(mode), 0, _vertex_count);    
        }
    };

private:
    static GLuint _newId();

    void _bindBuffers(const Buffer &data,
                      const Accessors &accessors,
                      const std::optional<const Buffer *> indices);

    const std::optional<ElementType> _indices_type;
    const GLuint _vertex_count;

};

}