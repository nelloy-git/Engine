#pragma once

namespace Graphics::Model {

enum class BufferType : unsigned int {
    Vertex = 0,
    Index,
    Other
};
const char *toString(BufferType type);

enum class BufferElemType : unsigned int {
    Byte = 0,
    UByte,
    Short,
    UShort,
    Int,
    UInt,
    Float,
    Double,
    Unknown
};
const char *toString(BufferElemType elem_type);
unsigned int getSize(BufferElemType elem_type);

enum class BufferElemStruct : unsigned int {
    Scalar = 0,
    Vec2,
    Vec3,
    Vec4,
    Mat2,
    Mat3,
    Mat4,
    Unknown
};
const char *toString(BufferElemStruct elem_struct);

enum class PrimitiveDrawMode : unsigned int {
    Points = 0,
    Line,
    LineLoop,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
    Unknown
};
const char *toString(PrimitiveDrawMode mode);

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
    Unknown
};
const char *toString(PrimitiveAttribute attr);
int getLocation(PrimitiveAttribute attr);
int getMorphTargetLocation(int target, PrimitiveAttribute attr);

enum class TextureFormat : unsigned int {
    RED,
    RG,
    RGB,
    RGBA,
    Unknown
};
const char *toString(TextureFormat fmt);

enum class TextureWrap : unsigned int {
    Repeat,
    ClampToEdge,
    MirroredRepeat,
    Unknown
};
const char *toString(TextureWrap wrap);

enum class TextureFilter : unsigned int {
    Linear,
    LinearMipmapLinear,
    LinearMipmapNearest,
    Nearest,
    NearestMipmapLinear,
    NearestMipmapNearest,
    Unknown
};
const char *toString(TextureFilter filter);

}