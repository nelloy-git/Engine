#include "Data/glTF.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace Graphics;

int glTF::getLayoutLocation(const std::string &name){
    if (name.compare("POSITION") == 0){
        return 0;
    } else if (name.compare("NORMAL") == 0){
        return 1;
    } else if (name.compare("TEXCOORD_0") == 0){
        return 2;
    } else {
        throw std::invalid_argument("Unknown glTF_attribute_name.");
    }
}

GLwrap::ComponentSize glTF::getComponentSize(int glTF_component_size){
    switch (glTF_component_size){
    case TINYGLTF_TYPE_SCALAR:
        return GLwrap::ComponentSize::Scalar;
    case TINYGLTF_TYPE_VEC2:
        return GLwrap::ComponentSize::Vec2;
    case TINYGLTF_TYPE_VEC3:
        return GLwrap::ComponentSize::Vec3;
    case TINYGLTF_TYPE_VEC4:
        return GLwrap::ComponentSize::Vec4;
    case TINYGLTF_TYPE_MAT2:
        return GLwrap::ComponentSize::Mat2;
    case TINYGLTF_TYPE_MAT3:
        return GLwrap::ComponentSize::Mat3;
    case TINYGLTF_TYPE_MAT4:
        return GLwrap::ComponentSize::Mat4;
    default:
        throw std::invalid_argument("Unknown glTF_component_size");
    }
}

GLwrap::ComponentType glTF::getComponentType(int glFT_component_type){
    switch (glFT_component_type){
    case TINYGLTF_COMPONENT_TYPE_BYTE:
        return GLwrap::ComponentType::Byte;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        return GLwrap::ComponentType::UByte;
    case TINYGLTF_COMPONENT_TYPE_SHORT:
        return GLwrap::ComponentType::Short;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        return GLwrap::ComponentType::UShort;
    case TINYGLTF_COMPONENT_TYPE_INT:
        return GLwrap::ComponentType::Int;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        return GLwrap::ComponentType::UInt;
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        return GLwrap::ComponentType::Float;
    case TINYGLTF_COMPONENT_TYPE_DOUBLE:
        return GLwrap::ComponentType::Double;
    default:
        throw std::invalid_argument("Unknown glTF_component_type");
    }
}

GLwrap::DrawMode glTF::getDrawMode(int glTF_draw_mode){
    switch (glTF_draw_mode){
    case TINYGLTF_MODE_POINTS:
        return GLwrap::DrawMode::POINTS;
    case TINYGLTF_MODE_LINE:
        return GLwrap::DrawMode::LINE;
    case TINYGLTF_MODE_LINE_LOOP:
        return GLwrap::DrawMode::LINE_LOOP;
    case TINYGLTF_MODE_LINE_STRIP:
        return GLwrap::DrawMode::LINE_STRIP;
    case TINYGLTF_MODE_TRIANGLES:
        return GLwrap::DrawMode::TRIANGLES;
    case TINYGLTF_MODE_TRIANGLE_STRIP:
        return GLwrap::DrawMode::TRIANGLE_STRIP;
    case TINYGLTF_MODE_TRIANGLE_FAN:
        return GLwrap::DrawMode::TRIANGLE_FAN;
    default:
        throw std::invalid_argument("Unknown glTF_draw_mode");
    }
}