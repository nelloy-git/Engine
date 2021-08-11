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

GLint Array::max_layouts(){
    static const GLint max = getMaxLayouts();
    return max;
}

Array::Array(const std::unordered_map<int, BufferPair> &layouts,
             const Buffer *indices, ElementType index_size) :
    id(_newId()),
    indexed(indices),
    _indeces_type(index_size){

    glBindVertexArray(id);

    for (auto iter : layouts){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        iter.second.first->bind();
        iter.second.second->enable(loc);
    }
    
    indices.bind();

    glBindVertexArray(0);
}

Array::Array(const std::unordered_map<int, BufferPair> &layouts) :
    id(_newId()),
    indexed(false){
    glBindVertexArray(id);

    for (auto iter : layouts){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        iter.second.first->bind();
        iter.second.second->enable(loc);
    }

    glBindVertexArray(0);
}

Array::Array(const Buffer &indices,
             const Buffer &data,
             const std::unordered_map<int, BufferAccessor *> &accessors) :
    id(_newId()),
    indexed(true){

    glBindVertexArray(id);

    data.bind();
    for (auto iter : accessors){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        auto acc = iter.second;
        if (acc){
            acc->enable(loc);
        }
    }
    
    indices.bind();

    glBindVertexArray(0);
}

Array::Array(const Buffer &data,
             const std::unordered_map<int, BufferAccessor *> &accessors) :
    id(_newId()),
    indexed(false){

    glBindVertexArray(id);

    data.bind();
    for (auto iter : accessors){
        auto loc = iter.first;
        if (loc > Array::max_layouts()){
            continue;
        }

        auto acc = iter.second;
        if (acc){
            acc->enable(loc);
        }
    }

    glBindVertexArray(0);
}

Array::~Array(){
    glDeleteVertexArrays(1, &id);
}

void Array::bind() const {
    glBindVertexArray(id);
}

void Array::unbind() const {
    glBindVertexArray(0);
}

void Array::drawArrays(DrawMode mode, GLuint first, GLuint count) const {
    glBindVertexArray(id);
    glDrawArrays(static_cast<GLenum>(mode), first, count);
    glBindVertexArray(0);
}

void Array::drawElements(DrawMode mode, ElementType type, GLuint vertex_count, GLuint64 byte_offset) const {
    glBindVertexArray(id);
    glDrawElements(static_cast<GLenum>(mode), vertex_count,
                   static_cast<GLenum>(type), (void*)byte_offset);
    glBindVertexArray(0);
}

GLuint Array::_newId(){
    GLuint id;
    glGenVertexArrays(1, &id);
    return id;
}