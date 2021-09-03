#pragma once

#include <vector>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

template<typename T>  
class BufferTyped : public Buffer {
public:
    BufferTyped(BufferType type, const std::vector<T> &list, BufferUsage usage = BufferUsage::STATIC) :
        Buffer(type, list.size() * sizeof(T)),
        size(list.size()){
        write(list.data());
    };
    virtual ~BufferTyped(){};

    void set(unsigned int i, const T &data){
        write(&data, i * sizeof(T), sizeof(T));
    }

    T get(unsigned int i){
        T tmp;
        read(&tmp, i * sizeof(T), sizeof(T));
        return tmp;
    }

    const size_t size;
};

using BufferUint = BufferTyped<unsigned int>;

}