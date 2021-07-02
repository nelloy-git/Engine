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
    } else if (name.compare("TANGENT") == 0){
        return 3;
    } else {
        throw std::invalid_argument("Unknown glTF_attribute_name \"" + name + "\".");
    }
}

ComponentSize glTF::getComponentSize(int glTF_component_size){
    switch (glTF_component_size){
    case TINYGLTF_TYPE_SCALAR:
        return ComponentSize::Scalar;
    case TINYGLTF_TYPE_VEC2:
        return ComponentSize::Vec2;
    case TINYGLTF_TYPE_VEC3:
        return ComponentSize::Vec3;
    case TINYGLTF_TYPE_VEC4:
        return ComponentSize::Vec4;
    case TINYGLTF_TYPE_MAT2:
        return ComponentSize::Mat2;
    case TINYGLTF_TYPE_MAT3:
        return ComponentSize::Mat3;
    case TINYGLTF_TYPE_MAT4:
        return ComponentSize::Mat4;
    default:
        throw std::invalid_argument("Unknown glTF_component_size \"" + std::to_string(glTF_component_size) + "\".");
    }
}

ComponentType glTF::getComponentType(int glFT_component_type){
    switch (glFT_component_type){
    case TINYGLTF_COMPONENT_TYPE_BYTE:
        return ComponentType::Byte;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        return ComponentType::UByte;
    case TINYGLTF_COMPONENT_TYPE_SHORT:
        return ComponentType::Short;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        return ComponentType::UShort;
    case TINYGLTF_COMPONENT_TYPE_INT:
        return ComponentType::Int;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        return ComponentType::UInt;
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        return ComponentType::Float;
    case TINYGLTF_COMPONENT_TYPE_DOUBLE:
        return ComponentType::Double;
    default:
        throw std::invalid_argument("Unknown glTF_component_type \"" + std::to_string(glFT_component_type) + "\".");
    }
}

size_t getComponentTypeSize(ComponentType type){
    switch (type){
        case ComponentType::Byte:
            return sizeof(GLbyte);
        case ComponentType::UByte:
            return sizeof(GLubyte);
        case ComponentType::Short:
            return sizeof(GLshort);
        case ComponentType::UShort:
            return sizeof(GLushort);
        case ComponentType::Int:
            return sizeof(GLint);
        case ComponentType::UInt:
            return sizeof(GLuint);
        case ComponentType::Float:
            return sizeof(GLfloat);
        case ComponentType::Double:
            return sizeof(GLdouble);
        default:
            throw std::invalid_argument("Unknown ComponentType.");
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
        throw std::invalid_argument("Unknown glTF_draw_mode \"" + std::to_string(glTF_draw_mode) + "\".");
    }
}

GLwrap::Tex2Dformat glTF::getImageFormat(int channels){
    switch (channels){
    case 1:
        return GLwrap::Tex2Dformat::RED;
    case 2:
        return GLwrap::Tex2Dformat::RG;
    case 3:
        return GLwrap::Tex2Dformat::RGB;
    case 4:
        return GLwrap::Tex2Dformat::RGBA;
    default:
        throw std::invalid_argument("wrong channels count \"" + std::to_string(channels) + "\".");
    }
}

GLuint glTF::getImageWrap(int glTF_wrap){
    switch (glTF_wrap){
    case TINYGLTF_TEXTURE_WRAP_REPEAT:
        return GL_REPEAT;
    case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
    default:
        throw std::invalid_argument("Unknown glTF_wrap \"" + std::to_string(glTF_wrap) + "\".");
    }
}

GLuint glTF::getImageFilter(int glTF_filter){
    switch (glTF_filter){
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
        return GL_LINEAR;
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
        return GL_LINEAR_MIPMAP_LINEAR;
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
        return GL_LINEAR_MIPMAP_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_NEAREST:
        return GL_NEAREST;
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
        return GL_NEAREST_MIPMAP_LINEAR;
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
        return GL_NEAREST_MIPMAP_NEAREST;
    default:
        throw std::invalid_argument("Unknown glTF_filter\"" + std::to_string(glTF_filter) + "\".");
    }
}