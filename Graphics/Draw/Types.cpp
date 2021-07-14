#include "Draw/Types.h"

using namespace Graphics;

unsigned int Draw::getSize(BufferElemType elem_type){
    switch (elem_type){
        case Draw::BufferElemType::Byte:
            return sizeof(char);
        case Draw::BufferElemType::UByte:
            return sizeof(unsigned char);
        case Draw::BufferElemType::Short:
            return sizeof(short);
        case Draw::BufferElemType::UShort:
            return sizeof(unsigned short);
        case Draw::BufferElemType::Int:
            return sizeof(int);
        case Draw::BufferElemType::UInt:
            return sizeof(unsigned int);
        case Draw::BufferElemType::Float:
            return sizeof(float);
        case Draw::BufferElemType::Double:
            return sizeof(double);
        default:
            return 0;
    }
}

unsigned int Draw::getSize(BufferElemStruct elem_struct){
    switch (elem_struct){
        case Draw::BufferElemStruct::Scalar:
            return 1;
        case Draw::BufferElemStruct::Vec2:
            return 2;
        case Draw::BufferElemStruct::Vec3:
            return 3;
        case Draw::BufferElemStruct::Vec4:
            return 4;
        case Draw::BufferElemStruct::Mat2:
            return 4;
        case Draw::BufferElemStruct::Mat3:
            return 9;
        case Draw::BufferElemStruct::Mat4:
            return 16;
        default:
            return 0;
    }
}

int Draw::getLocation(Draw::PrimitiveAttribute attr){
    switch (attr){
        case Draw::PrimitiveAttribute::Position:
            return 0;
        case Draw::PrimitiveAttribute::Normal:
            return 1;
        case Draw::PrimitiveAttribute::Tangent:
            return 2;
        case Draw::PrimitiveAttribute::TexCoord_0:
            return 3;
        case Draw::PrimitiveAttribute::TexCoord_1:
            return 4;
        case Draw::PrimitiveAttribute::Color_0:
            return 5;
        case Draw::PrimitiveAttribute::Joints_0:
            return 6;
        case Draw::PrimitiveAttribute::Joints_1:
            return 7;
        case Draw::PrimitiveAttribute::Weights_0:
            return 8;
        case Draw::PrimitiveAttribute::Weights_1:
            return 9;
        default:
            return -1;
    }
};

std::string Draw::getMorphTargetName(int target, PrimitiveAttribute attr){
    return "Target" + std::to_string(target) + "_" + toString(attr);
}

int Draw::getMorphTargetLocation(int target, PrimitiveAttribute attr){
    int base = 10 + 3 * target;

    // Based on getLocation.
    switch (attr){
        case Draw::PrimitiveAttribute::Position:
            return base;
        case Draw::PrimitiveAttribute::Normal:
            return base + 1;
        case Draw::PrimitiveAttribute::Tangent:
            return base + 2;
        default:
            return -1;
    }
}
