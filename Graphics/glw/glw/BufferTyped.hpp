#pragma once

#include <vector>

#include "glad/gl.h"

#include "glw/Buffer.hpp"

namespace glw {

template<class DT, BufferType BT, BufferUsage BU>  
class BufferTyped : public Buffer<BT, BU> {
public:

    explicit BufferTyped() :
        Buffer<BT, BU>(){
    };

    explicit BufferTyped(const std::vector<DT> &data) :
        Buffer<BT, BU>(){
        resize(data.size());
        write(0, data);
    }

    BufferTyped(const BufferTyped &) = delete;

    virtual ~BufferTyped(){
    };

    inline void write(size_t n, const DT &data){
        Buffer<BT, BU>::write(&data, n * sizeof(DT), sizeof(DT));
    };

    inline void write(size_t start_n, const std::vector<DT> &data){
        Buffer<BT, BU>::write(data.data(), start_n * sizeof(DT), data.size() * sizeof(DT));
    };

    inline std::unique_ptr<DT> read(size_t n){
        auto mem = malloc(sizeof(DT));
        Buffer<BT, BU>::read(mem, n * sizeof(DT), sizeof(DT));
        return mem;
    }

    inline std::unique_ptr<std::vector<DT>> read(size_t start_n, size_t count){
        auto list = new std::vector<DT>(count);
        Buffer<BT, BU>::read(list->data(), start_n * sizeof(DT), count * sizeof(DT));
        return list;
    }

    inline void resize(size_t count){
        Buffer<BT, BU>::resize(count * sizeof(DT));
        _count = count;
    }

    inline size_t count() const {
        return _count;
    }

protected:
    inline virtual void write(const void *data, GLintptr offset, GLsizeiptr size) override {
        return Buffer<BT, BU>::write(data, offset, size);
    }

    inline virtual void read(void *data, GLintptr offset, GLsizeiptr size) const override {
        return Buffer<BT, BU>::read(data, offset, size);
    }

    inline virtual void resize(GLsizeiptr size) override {
        return Buffer<BT, BU>::resize(size);
    }

    inline virtual GLsizeiptr size() override {
        return Buffer<BT, BU>::size();
    }

    size_t _count;
};

}