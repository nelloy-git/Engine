#include "Model/Types.h"

using namespace Graphics;

constexpr inline const char *Model::toString(Model::BufferType type){
    constexpr const char *map[] = {
        "Vertex",
        "Index",
        "Other"
    };

    return map[Model::toUint(type)];
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
        "Double"
    };

    return map[Model::toUint(elem_type)];
}

constexpr inline unsigned int Model::toUint(Model::BufferElemType elem_type){
    return static_cast<unsigned int>(elem_type);
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
    };

    return map[Model::toUint(mode)];
}

constexpr inline unsigned int Model::toUint(Model::PrimitiveDrawMode mode){
    return static_cast<unsigned int>(mode);
}

constexpr inline const char *Model::toString(Model::PrimitiveAttribute attr){
    constexpr const char* map[10] = {
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
    };
    
    return map[toUint(attr)];
}

constexpr inline unsigned int Model::toUint(Model::PrimitiveAttribute attr){
    return static_cast<unsigned int>(attr);
}