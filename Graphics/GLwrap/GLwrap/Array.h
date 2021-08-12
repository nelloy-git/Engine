#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "glad/gl.h"

#include "GLwrap/BufferAccessor.h"
#include "GLwrap/BufferTyped.h"

namespace GLwrap {

class Array {
public:
    using Layout = unsigned int;

    // Only one buffer
    // template<ElementType E>
    Array(const Buffer &data,
          const std::unordered_map<int, const BufferAccessor &> &accessors,
          const BufferTyped<toType<E>()> *indices = nullptr){
        id(_newId()),
        indexed(true){

        // glBindVertexArray(id);

        // data.bind();
        // for (auto iter : accessors){
        //     auto loc = iter.first;
        //     if (loc > Array::max_layouts()){
        //         continue;
        //     }
        //     iter.second.enable(loc);
        // }
        
        // if (indices){
        //     indices->bind();
        // };

        // glBindVertexArray(0);
    };

    using BufferPair = std::pair<const GLwrap::Buffer &,
                                 const GLwrap::BufferAccessor &>;

    // Multiple buffers
    Array(const std::unordered_map<Layout, BufferPair> &layouts,
          const BufferUint *indices = nullptr);


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