#pragma once

#include <unordered_map>

#include "magic_enum.h"

namespace Graphics::Draw {

enum class BufferType{
    Vertex,
    Index,
    Other,
    Unknown
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

enum class Interpolation {
    Linear,
    Unknown
};

enum class TextureUsage {
    Texture0,
    Texture1,
    Unknown
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
    static std::string type_name = toString<T>();
    static std::unordered_map<T, std::string> val2str;

    auto iter = val2str.find(enum_value);
    std::string name;
    if (iter == val2str.end()){
        name = magic_enum::enum_name(enum_value);
        val2str[enum_value] = name;
    } else {
        name = iter->second;
    }

    return full ? type_name + "::" + name : name;
}

template<typename T>
constexpr int enumCount(){
    return static_cast<int>(T::Unknown);
}

}