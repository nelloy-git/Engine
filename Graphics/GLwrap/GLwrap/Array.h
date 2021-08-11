#pragma once

#include <unordered_map>
#include <memory>
#include <utility>

#include "glad/gl.h"

#include "GLwrap/BufferAccessor.h"
#include "GLwrap/Buffer.h"

namespace GLwrap {

class Array {
public:
    using BufferPair = std::pair<const GLwrap::Buffer*,
                                 const GLwrap::BufferAccessor*>;

    // Multiple buffers
    Array(const std::unordered_map<int, BufferPair> &layouts,
          const Buffer *indices = nullptr, ElementType index_size = ElementType::Short);

    // Multiple buffers
    Array(const std::unordered_map<int, BufferPair> &layouts);

    // Only one buffer
    Array(const Buffer &indices,
          const Buffer &data,
          const std::unordered_map<int, BufferAccessor *> &accessors);

    // Only one buffer
    Array(const Buffer &data,
          const std::unordered_map<int, BufferAccessor *> &accessors);


    virtual ~Array();

    static GLint max_layouts();

    const GLuint id;
    const bool indexed;
    
    void bind() const;
    void unbind() const;

    void draw() const;
    void drawArrays(DrawMode mode, GLuint first, GLuint count) const;
    void drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset) const;

private:
    const ElementType _indeces_type;
    const GLuint _indices_count;

    static GLuint _newId();
};

}