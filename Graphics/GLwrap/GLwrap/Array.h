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

    Array(const Buffer &indices, 
          const std::unordered_map<int, BufferPair> &layouts);
    Array(const std::unordered_map<int, BufferPair> &layouts);
    virtual ~Array();

    static GLint max_layouts();

    const GLuint id;

    void bind();
    void unbind();
    
    void bind() const;
    void unbind() const;

    void drawArrays(DrawMode mode, GLuint first, GLuint count);
    void drawArrays(DrawMode mode, GLuint first, GLuint count) const;

    void drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset);
    void drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset) const;

private:
    static GLuint _newId();
};

}