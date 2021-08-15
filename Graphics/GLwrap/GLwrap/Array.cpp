#include "GLwrap/Array.h"

#include <stdexcept>
#include <unordered_map>

#include "Log.h"

using namespace GLwrap;

GLint getMaxLayouts(){
    GLint _max;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_max);
    return _max;
}

GLint BufferArray::max_layouts(){
    static const GLint max = getMaxLayouts();
    return max;
}

BufferArray::BufferArray(const Buffer &data,
                         const std::unordered_map<Layout, const BufferAccessor *> &accessors) :
    id(_newId()),
    indexed(false),
    _indices_type({}),
    _indices_count(0){
    _bindBuffers(data, accessors, {});
}

BufferArray::BufferArray(const std::unordered_map<Layout, BufferPair> &layouts) :
    id(_newId()),
    indexed(false),
    _indices_type({}),
    _indices_count(0){
    _bindBuffers(layouts, {});
}

BufferArray::~BufferArray(){
    glDeleteVertexArrays(1, &id);
}

void BufferArray::bind() const {
    glBindVertexArray(id);
}

void BufferArray::unbind() const {
    glBindVertexArray(0);
}

void BufferArray::drawArrays(DrawMode mode, GLuint first, GLuint count) const {
    glBindVertexArray(id);
    glDrawArrays(static_cast<GLenum>(mode), first, count);
    glBindVertexArray(0);
}

void BufferArray::drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset) const {
    glBindVertexArray(id);
    glDrawElements(static_cast<GLenum>(mode), vertex_count,
                   static_cast<GLenum>(type), (void*)byte_offset);
    glBindVertexArray(0);
}

GLuint BufferArray::_newId(){
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}

void BufferArray::_bindBuffers(const Buffer &data,
                               const std::unordered_map<Layout, const BufferAccessor *> &accessors,
                               const std::optional<const Buffer *> indices){
    
    glBindVertexArray(id);

    data.bind();
    for (auto iter : accessors){
        auto loc = iter.first;
        if (loc > BufferArray::max_layouts()){
            continue;
        }

        auto acc = iter.second;
        if (acc) acc->enable(loc);
    }

    if (indices){
        indices.value()->bind();
    }

    glBindVertexArray(0);
}

void BufferArray::_bindBuffers(const std::unordered_map<Layout, BufferPair> &layouts,
                               const std::optional<const Buffer *> indices){
    
    glBindVertexArray(id);

    for (auto &iter : layouts){
        auto loc = iter.first;
        if (loc > BufferArray::max_layouts()){
            continue;
        }

        auto data = iter.second.first;
        auto acc = iter.second.second;

        data->bind();
        acc->enable(loc);
    }

    if (indices){
        indices.value()->bind();
    }

    glBindVertexArray(0);
}