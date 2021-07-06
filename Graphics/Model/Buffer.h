#pragma once

#include "GLwrap/Types.h"

namespace Graphics::Model {

class Buffer {
public:
    enum class ElemType : unsigned int {
        Byte = 0,
        UByte,
        Short,
        UShort,
        Int,
        UInt,
        Float,
        Double,
    };
    static constexpr inline const char *toString(ElemType elem_type);
    static constexpr inline unsigned int toUint(ElemType elem_type);
    static constexpr inline GLwrap::ComponentType toGL(ElemType elem_type);

    enum class ElemStruct : unsigned int {
        Scalar = 0,
        Vec2,
        Vec3,
        Vec4,
        Mat2,
        Mat3,
        Mat4,
    };
    static constexpr inline const char *toString(ElemStruct elem_struct);
    static constexpr inline unsigned int toUint(ElemStruct elem_struct);
    static constexpr inline GLwrap::ComponentSize toGL(ElemStruct elem_struct);

public:
    virtual bool write(const void *src, unsigned int size, unsigned int offset) = 0;
    virtual bool read(void *dst, unsigned int size, unsigned int offset) = 0;

    const ElemType data_type;
    const ElemStruct data_size;
    const bool normalized;
    const int count;

    const unsigned int bytes;

protected:
    Buffer(ElemType data_type, ElemStruct data_size, bool normalized, int count, unsigned int bytes) :
        data_type(data_type), data_size(data_size), normalized(normalized), count(count), bytes(bytes){
    };
    virtual ~Buffer(){};
};

}