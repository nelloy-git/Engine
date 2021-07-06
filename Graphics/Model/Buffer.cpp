#include "Model/Buffer.h"

using namespace Graphics::Model;

constexpr inline const char *Buffer::toString(Buffer::ElemType elem_type){
    constexpr const char *map[] = {
        "Byte",
        "UByte",
        "Short",
        "UShort",
        "Int",
        "UInt",
        "Float",
        "Double"
    };

    return map[Buffer::toUint(elem_type)];
}

constexpr inline unsigned int Buffer::toUint(ElemType elem_type){
    return static_cast<unsigned int>(elem_type);
}

constexpr inline GLwrap::ComponentType Buffer::toGL(ElemType elem_type){
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

constexpr inline const char *Buffer::toString(ElemStruct elem_struct){
    constexpr const char *map[] = {
        "Scalar",
        "Vec2",
        "Vec3",
        "Vec4",
        "Mat2",
        "Mat3",
        "Mat4",
    };

    return map[toUint(elem_struct)];
}

constexpr inline unsigned int Buffer::toUint(ElemStruct elem_struct){
    return static_cast<unsigned int>(elem_struct);
}

constexpr inline GLwrap::ComponentSize Buffer::toGL(ElemStruct elem_struct){
    constexpr GLwrap::ComponentSize map[] = {
        GLwrap::ComponentSize::Scalar,
        GLwrap::ComponentSize::Vec2,
        GLwrap::ComponentSize::Vec3,
        GLwrap::ComponentSize::Vec4,
        GLwrap::ComponentSize::Mat2,
        GLwrap::ComponentSize::Mat3,
        GLwrap::ComponentSize::Mat4
    };

    return map[toUint(elem_struct)];
}



// https://github.com/KhronosGroup/glTF-Sample-Viewer/blob/master/source/gltf/primitive.js