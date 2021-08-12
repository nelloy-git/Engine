#pragma once

#include <vector>

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

template<typename T>  
class BufferTyped : public Buffer {
public:
    BufferTyped(BufferType type, const std::vector<T> &list, BufferUsage usage = BufferUsage::STATIC) :
        Buffer(type, list.size() * sizeof(T)){
        write(&list[0]);
    };
    virtual ~BufferTyped();

    void set(uint i, const T &data){
        write(&data, i * sizeof(T), sizeof(T));
    }

    T get(uint i){
        T tmp;
        read(&tmp, i * sizeof(T), sizeof(T));
        return tmp;
    }

};

using BufferUint = BufferTyped<unsigned int>;

}