#pragma once

#include "glad/glad.h"

#include "VBO/utils/DataType.h"
#include "VBO/utils/UsageType.h"

namespace Graphics::VBO {

template<typename T>
class Object {
public:
    Object(DataType type) :
        type(type){

        auto pId = const_cast<GLuint*>(&id);
        glGenBuffers(1, pId);
    };

    virtual ~Object(){
        glDeleteBuffers(1, &id);
    };

    template<int n>
    void load(const T(&data)[n], UsageType usage){
        __size = n;
        __data = &data[0];
        __usage = usage;

        glBindBuffer(static_cast<GLenum>(type), id);
        glBufferData(static_cast<GLenum>(type), n * sizeof(T), &data, static_cast<GLenum>(usage));
        glBindBuffer(static_cast<GLenum>(type), 0);
    };

    virtual void bind(){
        glBindBuffer(static_cast<GLenum>(type), id);
    };

    virtual void unbind(){
        glBindBuffer(static_cast<GLenum>(type), 0);
    };

    const DataType type;
    const GLuint id = 0;

    int size();
    const T* ptr();
    UsageType usage();

private:
    const T* __data;
    GLsizeiptr __size;
    UsageType __usage;
};

}