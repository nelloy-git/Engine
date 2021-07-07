#include "Model/Buffer/BufferGL.h"

#include "GLwrap/Buffer.h"
#include "GLwrap/BufferAccessor.h"

using namespace Graphics::Model;

constexpr inline GLwrap::BufferType toGL(BufferType type){
    constexpr GLwrap::BufferType map[] = {
        GLwrap::BufferType::ARRAY,
        GLwrap::BufferType::ELEMENT_ARRAY,
    };

    return map[toUint(type)];
}

constexpr inline GLwrap::ComponentType toGL(BufferElemType elem_type){
    constexpr GLwrap::ComponentType map[] = {
        GLwrap::ComponentType::Byte,
        GLwrap::ComponentType::UByte,
        GLwrap::ComponentType::Short,
        GLwrap::ComponentType::UShort,
        GLwrap::ComponentType::Int,
        GLwrap::ComponentType::UInt,
        GLwrap::ComponentType::Float,
        GLwrap::ComponentType::Double,
    };

    return map[toUint(elem_type)];
}

constexpr inline GLwrap::ComponentSize toGL(BufferElemStruct elem_type){
    constexpr GLwrap::ComponentSize map[] = {
        GLwrap::ComponentSize::Scalar,
        GLwrap::ComponentSize::Vec2,
        GLwrap::ComponentSize::Vec3,
        GLwrap::ComponentSize::Vec4,
        GLwrap::ComponentSize::Mat2,
        GLwrap::ComponentSize::Mat3,
        GLwrap::ComponentSize::Mat4
    };

    return map[toUint(elem_type)];
}

BufferGL::BufferGL(BufferType type, BufferElemType data_type, BufferElemStruct data_size,
                   unsigned int count, unsigned int bytes, bool normalized) : 
    Buffer(type, data_type, data_size, normalized, count, bytes){

    accessor = std::make_shared<GLwrap::BufferAccessor>(toGL(data_size), toGL(data_type), normalized, 0, 0);
    data = std::make_shared<GLwrap::Buffer>(toGL(type), bytes);
}

BufferGL::~BufferGL(){
}

bool BufferGL::write(const void *src, unsigned int size, unsigned int offset){
    return data->write(src, offset, size);
}

bool BufferGL::read(void *dst, unsigned int size, unsigned int offset){
    return data->read(dst, offset, size);
}