#pragma once

#include "magic_enum.h"

namespace Graphics::Draw {

enum class BufferType{
    Vertex,
    Index,
    Other
};

// Unknown must be last one.
enum class BufferElemType{
    Byte,
    UByte,
    Short,
    UShort,
    Int,
    UInt,
    Float,
    Double,
    Unknown
};
unsigned int getSize(BufferElemType elem_type);

// Unknown must be last one.
enum class BufferElemStruct{
    Scalar,
    Vec2,
    Vec3,
    Vec4,
    Mat2,
    Mat3,
    Mat4,
    Unknown
};
unsigned int getSize(BufferElemStruct elem_struct);

// Unknown must be last one.
enum class PrimitiveDrawMode{
    Points,
    Line,
    LineLoop,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
    Unknown
};

// Unknown must be last one.
enum class PrimitiveAttribute{
    Position,
    Normal,
    Tangent,
    TexCoord_0,
    TexCoord_1,
    Color_0,
    Joints_0,
    Weights_0,
    Unknown
};
int getLocation(PrimitiveAttribute attr);
std::string getMorphTargetName(int target, PrimitiveAttribute attr);
int getMorphTargetLocation(int target, int total_targets, PrimitiveAttribute attr);

// Unknown must be last one.
enum class TextureFormat{
    RED,
    RG,
    RGB,
    RGBA,
    Unknown
};

// Unknown must be last one.
enum class TextureWrap{
    Repeat,
    ClampToEdge,
    MirroredRepeat,
    Unknown
};

// Unknown must be last one.
enum class TextureFilter{
    Linear,
    LinearMipmapLinear,
    LinearMipmapNearest,
    Nearest,
    NearestMipmapLinear,
    NearestMipmapNearest,
    Unknown
};

enum class TextureUsage {
    Texture0,
    Texture1
};
int getLocation(TextureUsage usage);

template<typename T>
constexpr std::string toString(){
    char const* p = __PRETTY_FUNCTION__;
    while (*p++ != '=');
    for (; *p == ' '; ++p);
    char const* p2 = p;
    int count = 1;
    for (;;++p2)
    {
        switch (*p2)
        {
        case '[':
            ++count;
            break;
        case ';':
        case ']':
            --count;
            if (!count)
                return {p, std::size_t(p2 - p)};
        }
    }
    return {};
}

template<typename T>
std::string toString(T enum_value, bool full = false){
    static_assert(std::is_enum_v<T> && std::is_same_v<T, std::decay_t<T>>, "Enum type is required.");

    std::string str;
    if (full){
        constexpr auto type_name = magic_enum::enum_type_name<T>();
        str = std::string(type_name) + "::";
    }
    auto enum_name = magic_enum::enum_name(enum_value);
    str += std::string(enum_name);

    return str;
}

template<typename T>
constexpr int enumCount(){
    return static_cast<int>(T::Unknown);
}

}