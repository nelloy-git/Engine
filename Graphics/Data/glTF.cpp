#include "Data/glTF.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace Graphics::glTF;

int getAttrLoc(const std::string &name){
    if (name.compare("POSITION") == 0){
        return 0;
    } else if (name.compare("NORMAL") == 0){
        return 1;
    } else if (name.compare("TEXCOORD_0") == 0){
        return 2;
    } else {
        return -1;
    }
}

GLwrap::ShaderDataSize getAttrComponentSize(int glTF_component_size){
    switch (glTF_component_size){
    case TINYGLTF_TYPE_SCALAR:
        return GLwrap::ShaderDataSize::Scalar;
    case TINYGLTF_TYPE_VEC2:
        return GLwrap::ShaderDataSize::Vec2;
    case TINYGLTF_TYPE_VEC3:
        return GLwrap::ShaderDataSize::Vec3;
    case TINYGLTF_TYPE_VEC4:
        return GLwrap::ShaderDataSize::Vec4;
    case TINYGLTF_TYPE_MAT2:
        return GLwrap::ShaderDataSize::Mat2;
    case TINYGLTF_TYPE_MAT3:
        return GLwrap::ShaderDataSize::Mat3;
    case TINYGLTF_TYPE_MAT4:
        return GLwrap::ShaderDataSize::Mat4;
    default:
        throw std::invalid_argument("Unknown glTF_component_size");
    }
}

GLwrap::ShaderDataType getAttrComponentType(int glFT_component_type){
    switch (glFT_component_type){
    case TINYGLTF_COMPONENT_TYPE_BYTE:
        return GLwrap::ShaderDataType::Byte;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        return GLwrap::ShaderDataType::UByte;
    case TINYGLTF_COMPONENT_TYPE_SHORT:
        return GLwrap::ShaderDataType::Short;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        return GLwrap::ShaderDataType::UShort;
    case TINYGLTF_COMPONENT_TYPE_INT:
        return GLwrap::ShaderDataType::Int;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        return GLwrap::ShaderDataType::UInt;
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        return GLwrap::ShaderDataType::Float;
    case TINYGLTF_COMPONENT_TYPE_DOUBLE:
        return GLwrap::ShaderDataType::Double;
    default:
        throw std::invalid_argument("Unknown glTF_component_type");
    }
}

GLwrap::VAOdrawMode getDrawMode(int glTF_draw_mode){
    switch (glTF_draw_mode){
    case TINYGLTF_MODE_POINTS:
        return GLwrap::VAOdrawMode::POINTS;
    case TINYGLTF_MODE_LINE:
        return GLwrap::VAOdrawMode::LINE;
    case TINYGLTF_MODE_LINE_LOOP:
        return GLwrap::VAOdrawMode::LINE_LOOP;
    case TINYGLTF_MODE_LINE_STRIP:
        return GLwrap::VAOdrawMode::LINE_STRIP;
    case TINYGLTF_MODE_TRIANGLES:
        return GLwrap::VAOdrawMode::TRIANGLES;
    case TINYGLTF_MODE_TRIANGLE_STRIP:
        return GLwrap::VAOdrawMode::TRIANGLE_STRIP;
    case TINYGLTF_MODE_TRIANGLE_FAN:
        return GLwrap::VAOdrawMode::TRIANGLE_FAN;
    default:
        throw std::invalid_argument("Unknown glTF_draw_mode");
    }
}