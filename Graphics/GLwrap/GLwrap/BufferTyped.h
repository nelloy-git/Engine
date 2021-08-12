#pragma once

#include "glad/gl.h"

#include "GLwrap/Buffer.h"

namespace GLwrap {

template<typename T>  
class BufferTyped : public Buffer {
public:
    BufferTyped(BufferType type, const std::vector<T> &list, BufferUsage usage = BufferUsage::STATIC) :
        Buffer(type, list.size() * sizeof(T)){
        // write()
    };
    virtual ~BufferTyped();

    /* if (size == 0){size = this->size;} */
    bool write(const void *data, size_t  offset = 0, size_t size = 0);

    /* if (size == 0){size = this->size;} */
    bool read(void *data, size_t  offset = 0, size_t  size = 0) const;

    void bind() const;
    void unbind() const;

    const GLuint id;
    const size_t size;
    const BufferType type;
    const BufferUsage usage;

protected:
    inline virtual bool write(const void *data, size_t  offset = 0, size_t size = 0) override{
        Buffer::write(data, offset, size);
    };

    inline virtual bool read(void *data, size_t  offset = 0, size_t  size = 0) const override{
        Buffer::read(data, offset, size);
    };


private:
    static GLuint _newId();
};

}