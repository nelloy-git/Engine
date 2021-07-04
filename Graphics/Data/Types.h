#pragma once

#include "GLwrap/Types.h"

namespace Graphics {

enum class ComponentType : std::underlying_type_t<GLwrap::ComponentType> {
    Byte = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::Byte),
    UByte = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::UByte),
    Short = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::Short),
    UShort = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::UShort),
    Int = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::Int),
    UInt = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::UInt),
    Float = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::Float),
    Double = static_cast<std::underlying_type_t<GLwrap::ComponentType>>(GLwrap::ComponentType::Double),
};

enum class ComponentSize : std::underlying_type_t<GLwrap::ComponentSize> {
    Scalar = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Scalar),
    Vec2 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Vec2),
    Vec3 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Vec3),
    Vec4 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Vec4),
    Mat2 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Mat2),
    Mat3 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Mat3),
    Mat4 = std::underlying_type_t<GLwrap::ComponentSize>(GLwrap::ComponentSize::Mat4),
};

}