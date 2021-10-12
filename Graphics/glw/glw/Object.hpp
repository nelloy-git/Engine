#pragma once

#include <memory>
#include <vector>

#include "glw/BufferTyped.hpp"
#include "glw/Vertex.hpp"

namespace glw {

template<class V>
class Object {
    static_assert(detailed::is_base_of_template<Vertex, V>::value);

    using VertexBuffer = BufferTyped<V, BufferType::Data, BufferUsage::STATIC>;

public:
    Object(const std::vector<V> &vertices) :
        id(_newId()),
        _count(vertices.size()),
        _vert(vertices){

        glBindVertexArray(id);
        _vert.bind();
        V::bindAttributes();
    }

    virtual ~Object(){
        glDeleteVertexArrays(1, &id);
    }

    virtual bool indexed(){
        return false;
    }

    virtual inline void draw(DrawMode mode) const {
        glBindVertexArray(id);
        glDrawArrays(gl(mode), 0, _count);
    };
        
    const GLuint id;

private:
    static GLuint _newId(){
        GLuint id;
        glGenVertexArrays(1, &id);
        return id;
    }

    const VertexBuffer _vert;
    const GLuint _count;
};

template<class V>
class ObjectIndexed : public Object<V> {
    using CharBuffer = BufferTyped<GLubyte, BufferType::Index, BufferUsage::STATIC>;
    using ShortBuffer = BufferTyped<GLushort, BufferType::Index, BufferUsage::STATIC>;
    using IntBuffer = BufferTyped<GLuint, BufferType::Index, BufferUsage::STATIC>;

    template<class T>
    using IndexBuffer = BufferTyped<T, BufferType::Index, BufferUsage::STATIC>;

public:

    template<class T>
    ObjectIndexed(const std::vector<V> &vertices,
                  const std::vector<T> &indices) :
        Object<V>(vertices),
        _count(indices.size()),
        _indices_type(_getGpuType<T>()),
        _index(std::in_place_type<IndexBuffer<T>>, indices){
        std::get<IndexBuffer<T>>(_index).bind();
    }

    virtual bool indexed(){
        return true;
    }

    virtual inline void draw(DrawMode mode) const {
        glBindVertexArray(Object<V>::id);
        glDrawElements(gl(mode), _count, gl(_indices_type), (void*)0);
    };

private:

    template<class T>
    static constexpr gpu_data_type _getGpuType(){
        if constexpr (std::is_same_v<T, GLubyte>){return gpu_data_type::GLubyte;}
        else if constexpr (std::is_same_v<T, GLushort>){return gpu_data_type::GLushort;}
        else if constexpr (std::is_same_v<T, GLuint>){return gpu_data_type::GLuint;}
        else {[]<bool F = false>(){static_assert(F, "Wrong indices type");};}
    }

    std::variant<CharBuffer, ShortBuffer, IntBuffer> _index;
    GLuint _count;
    const gpu_data_type _indices_type;
};

}