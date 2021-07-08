#pragma once

#include "GLwrap/Types.h"

namespace Graphics {

enum class ComponentType : std::underlying_type_t<GLwrap::ElementType> {
    Byte = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::Byte),
    UByte = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::UByte),
    Short = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::Short),
    UShort = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::UShort),
    Int = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::Int),
    UInt = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::UInt),
    Float = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::Float),
    Double = static_cast<std::underlying_type_t<GLwrap::ElementType>>(GLwrap::ElementType::Double),
};

enum class ComponentSize : std::underlying_type_t<GLwrap::ElementStruct> {
    Scalar = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Scalar),
    Vec2 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Vec2),
    Vec3 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Vec3),
    Vec4 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Vec4),
    Mat2 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Mat2),
    Mat3 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Mat3),
    Mat4 = std::underlying_type_t<GLwrap::ElementStruct>(GLwrap::ElementStruct::Mat4),
};

}