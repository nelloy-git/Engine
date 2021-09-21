#include "Types.h"

size_t GLwrap::getSize(ElementType elem_type){
    switch (elem_type){
        case ElementType::Byte:
            return sizeof(char);
        case ElementType::UByte:
            return sizeof(unsigned char);
        case ElementType::Short:
            return sizeof(short);
        case ElementType::UShort:
            return sizeof(unsigned short);
        case ElementType::Int:
            return sizeof(int);
        case ElementType::UInt:
            return sizeof(unsigned int);
        case ElementType::Float:
            return sizeof(float);
        case ElementType::Double:
            return sizeof(double);
        default:
            return 0;
    }
}

unsigned int GLwrap::getCount(ElementStruct elem_struct){
    switch (elem_struct){
        case ElementStruct::Scalar:
            return 1;
        case ElementStruct::Vec2:
            return 2;
        case ElementStruct::Vec3:
            return 3;
        case ElementStruct::Vec4:
            return 4;
        // case ElementStruct::Mat2:
        //     return 4;
        case ElementStruct::Mat3:
            return 9;
        case ElementStruct::Mat4:
            return 16;
        default:
            return 0;
    }
}