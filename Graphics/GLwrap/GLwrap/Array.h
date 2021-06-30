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
    typedef std::pair<std::shared_ptr<GLwrap::Buffer>,
                      std::shared_ptr<GLwrap::BufferAccessor>> BufferPair;

    Array(std::shared_ptr<Buffer> indices, 
          const std::unordered_map<int, BufferPair> &layouts);
    virtual ~Array();

    GLuint id();

    void bind();
    void unbind();
    
    void bind() const;
    void unbind() const;

    void draw(DrawMode mode, ComponentType type, size_t vertex_count, size_t byte_offset);
    void draw(DrawMode mode, ComponentType type, size_t vertex_count, size_t byte_offset) const;

    std::shared_ptr<Buffer> indices;
    std::unordered_map<int, BufferPair> layouts;

private:
    GLuint _id = 0;
};

}