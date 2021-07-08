#include "Model/Types.h"

#include "GLwrap/Types.h"

using namespace Graphics;

constexpr inline const char *Model::toString(Model::BufferType type){
    switch (type){
        case Model::BufferType::Vertex:
            return "BufferType::Vertex";
        case Model::BufferType::Index:
            return "BufferType::Index";
        default:
            return "BufferType::Other";
    }
}

constexpr inline unsigned int Model::toUint(Model::BufferType type){
    return static_cast<unsigned int>(type);
}

constexpr inline const char *Model::toString(Model::BufferElemType elem_type){
    constexpr const char *map[] = {
        "Byte",
        "UByte",
        "Short",
        "UShort",
        "Int",
        "UInt",
        "Float",
        "Double",
        "Unknown"
    };

    return map[Model::toUint(elem_type)];
}

constexpr inline unsigned int Model::toUint(Model::BufferElemType elem_type){
    return static_cast<unsigned int>(elem_type);
}

constexpr inline unsigned int Model::getSize(BufferElemType elem_type){
    constexpr unsigned int map[] = {
        sizeof(GLbyte),
        sizeof(GLubyte),
        sizeof(GLshort),
        sizeof(GLushort),
        sizeof(GLint),
        sizeof(GLuint),
        sizeof(GLfloat),
        sizeof(GLdouble),
    };

    return map[Model::toUint(elem_type)];
}

constexpr inline const char *Model::toString(Model::BufferElemStruct elem_struct){
    constexpr const char *map[] = {
        "Scalar",
        "Vec2",
        "Vec3",
        "Vec4",
        "Mat2",
        "Mat3",
        "Mat4",
        "Unknown"
    };

    return map[Model::toUint(elem_struct)];
}

constexpr inline unsigned int Model::toUint(Model::BufferElemStruct elem_struct){
    return static_cast<unsigned int>(elem_struct);
}

constexpr inline const char *Model::toString(Model::PrimitiveDrawMode mode){
    constexpr const char *map[] = {
        "Points",
        "Line",
        "LineLoop",
        "LineStrip",
        "Triangles",
        "TrianglesStrip",
        "TrianglesFan",
        "Unknown"
    };

    return map[Model::toUint(mode)];
}

constexpr inline unsigned int Model::toUint(Model::PrimitiveDrawMode mode){
    return static_cast<unsigned int>(mode);
}

constexpr inline const char *Model::toString(Model::PrimitiveAttribute attr){
    constexpr const char* map[] = {
        "vPos",
        "vNorm",
        "vTang",
        "vTex0",
        "vTex1",
        "vCol",
        "vJoint0",
        "vJoint1",
        "vWeight0",
        "vWeight1",
        "Unknown"
    };
    
    return map[toUint(attr)];
}

constexpr inline unsigned int Model::toUint(Model::PrimitiveAttribute attr){
    return static_cast<unsigned int>(attr);
}

constexpr inline const char *Model::toString(TextureFormat fmt){
    constexpr const char *map[] = {
        "RED",
        "RG",
        "RGB",
        "RGBA",
        "Unknown"
    };

    return map[toUint(fmt)];
}

constexpr inline unsigned int Model::toUint(TextureFormat fmt){
    return static_cast<unsigned int>(fmt);
}

constexpr inline const char *Model::toString(TextureWrap wrap){
    constexpr const char *map[] = {
        "Repeat",
        "ClampToEdge",
        "MirroredRepeat",
        "Unknown"
    };

    return map[toUint(wrap)];
}

constexpr inline unsigned int Model::toUint(TextureWrap wrap){
    return static_cast<unsigned int>(wrap);
}

constexpr inline const char *Model::toString(TextureFilter filter){
    constexpr const char *map[] = {
        "Linear",
        "LinearMipmapLinear",
        "LinearMipmapNearest",
        "Nearest",
        "NearestMipmapLinear",
        "NearestMipmapNearest",
        "Unknown"
    };

    return map[toUint(filter)];
}

constexpr inline unsigned int Model::toUint(TextureFilter filter){
    return static_cast<unsigned int>(filter);
}