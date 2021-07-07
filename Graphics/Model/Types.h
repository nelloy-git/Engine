#pragma once

namespace Graphics::Model {

enum class BufferType : unsigned int {
    Vertex = 0,
    Index,
    Other
};
constexpr inline const char *toString(BufferType type);
constexpr inline unsigned int toUint(BufferType type);

enum class BufferElemType : unsigned int {
    Byte = 0,
    UByte,
    Short,
    UShort,
    Int,
    UInt,
    Float,
    Double,
};
constexpr inline const char *toString(BufferElemType elem_type);
constexpr inline unsigned int toUint(BufferElemType elem_type);

enum class BufferElemStruct : unsigned int {
    Scalar = 0,
    Vec2,
    Vec3,
    Vec4,
    Mat2,
    Mat3,
    Mat4,
};
constexpr inline const char *toString(BufferElemStruct elem_struct);
constexpr inline unsigned int toUint(BufferElemStruct elem_struct);

enum class PrimitiveDrawMode : unsigned int {
    Points = 0,
    Line,
    LineLoop,
    LineStrip,
    Triangles,
    TrianglesStrip,
    TrianglesFan
};
constexpr inline const char *toString(PrimitiveDrawMode mode);
constexpr inline unsigned int toUint(PrimitiveDrawMode mode);

enum class PrimitiveAttribute : unsigned int {
    Position = 0,
    Normal,
    Tangent,
    TexCoord_0,
    TexCoord_1,
    Color_0,
    Joints_0,
    Joints_1,
    Weights_0,
    Weights_1,
};
constexpr inline const char *toString(PrimitiveAttribute attr);
constexpr inline unsigned int toUint(PrimitiveAttribute attr);

}