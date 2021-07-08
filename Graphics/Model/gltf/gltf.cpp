#include "Model/gltf/gltf.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace Graphics::Model;

BufferType gltfConvert::getBufferType(int type){
    switch (type){
        case TINYGLTF_TARGET_ARRAY_BUFFER:
            return BufferType::Vertex;
        case TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER:
            return BufferType::Index;
        default:
           return BufferType::Other;
    }
}

BufferElemStruct gltfConvert::getBufferElemStruct(int gltfConvert_component_size){
    switch (gltfConvert_component_size){
    case TINYGLTF_TYPE_SCALAR:
        return BufferElemStruct::Scalar;
    case TINYGLTF_TYPE_VEC2:
        return BufferElemStruct::Vec2;
    case TINYGLTF_TYPE_VEC3:
        return BufferElemStruct::Vec3;
    case TINYGLTF_TYPE_VEC4:
        return BufferElemStruct::Vec4;
    case TINYGLTF_TYPE_MAT2:
        return BufferElemStruct::Mat2;
    case TINYGLTF_TYPE_MAT3:
        return BufferElemStruct::Mat3;
    case TINYGLTF_TYPE_MAT4:
        return BufferElemStruct::Mat4;
    default:
        return BufferElemStruct::Unknown;
    }
}

BufferElemType gltfConvert::getBufferElemType(int glFT_component_type){
    switch (glFT_component_type){
    case TINYGLTF_COMPONENT_TYPE_BYTE:
        return BufferElemType::Byte;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        return BufferElemType::UByte;
    case TINYGLTF_COMPONENT_TYPE_SHORT:
        return BufferElemType::Short;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        return BufferElemType::UShort;
    case TINYGLTF_COMPONENT_TYPE_INT:
        return BufferElemType::Int;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        return BufferElemType::UInt;
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        return BufferElemType::Float;
    case TINYGLTF_COMPONENT_TYPE_DOUBLE:
        return BufferElemType::Double;
    default:
        throw BufferElemType::Unknown;
    }
}

// size_t gltfConvert::getComponentTypeSize(ComponentType type){
//     switch (type){
//         case ComponentType::Byte:
//             return sizeof(GLbyte);
//         case ComponentType::UByte:
//             return sizeof(GLubyte);
//         case ComponentType::Short:
//             return sizeof(GLshort);
//         case ComponentType::UShort:
//             return sizeof(GLushort);
//         case ComponentType::Int:
//             return sizeof(GLint);
//         case ComponentType::UInt:
//             return sizeof(GLuint);
//         case ComponentType::Float:
//             return sizeof(GLfloat);
//         case ComponentType::Double:
//             return sizeof(GLdouble);
//         default:
//             throw std::invalid_argument("Unknown ComponentType.");
//     }
// }

PrimitiveDrawMode gltfConvert::getDrawMode(int gltfConvert_draw_mode){
    switch (gltfConvert_draw_mode){
    case TINYGLTF_MODE_POINTS:
        return PrimitiveDrawMode::Points;
    case TINYGLTF_MODE_LINE:
        return PrimitiveDrawMode::Line;
    case TINYGLTF_MODE_LINE_LOOP:
        return PrimitiveDrawMode::LineLoop;
    case TINYGLTF_MODE_LINE_STRIP:
        return PrimitiveDrawMode::LineStrip;
    case TINYGLTF_MODE_TRIANGLES:
        return PrimitiveDrawMode::Triangles;
    case TINYGLTF_MODE_TRIANGLE_STRIP:
        return PrimitiveDrawMode::TriangleStrip;
    case TINYGLTF_MODE_TRIANGLE_FAN:
        return PrimitiveDrawMode::TriangleFan;
    default:
        throw PrimitiveDrawMode::Unknown;
    }
}

PrimitiveAttribute gltfConvert::getAttribute(const std::string &gltf_attr){
    if (gltf_attr == "POSITION"){
        return PrimitiveAttribute::Position;
    } else if (gltf_attr == "NORMAL"){  
        return PrimitiveAttribute::Normal;
    } else if (gltf_attr == "TANGENT"){
        return PrimitiveAttribute::Tangent;
    } else if (gltf_attr == "TEXCOORD_0"){
        return PrimitiveAttribute::TexCoord_0;
    } else if (gltf_attr == "TEXCOORD_1"){
        return PrimitiveAttribute::TexCoord_1;
    } else if (gltf_attr == "COLOR_0"){
        return PrimitiveAttribute::Color_0;
    } else if (gltf_attr == "JOINTS_0"){
        return PrimitiveAttribute::Joints_0;
    } else if (gltf_attr == "JPINTS_1"){
        return PrimitiveAttribute::Joints_1;
    } else if (gltf_attr == "WEIGHTS_0"){
        return PrimitiveAttribute::Weights_0;
    } else if (gltf_attr == "WEIGHTS_1"){
        return PrimitiveAttribute::Weights_1;
    } else {
        return PrimitiveAttribute::Unknown;
    }
}

TextureFilter gltfConvert::getTextureFilter(int gltf_filter){
    switch (gltf_filter){
        case TINYGLTF_TEXTURE_FILTER_LINEAR: 
            return TextureFilter::Linear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: 
            return TextureFilter::LinearMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: 
            return TextureFilter::LinearMipmapNearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST: 
            return TextureFilter::Nearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: 
            return TextureFilter::NearestMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: 
            return TextureFilter::NearestMipmapNearest;
        default:
            return TextureFilter::Unknown;
    }
}

TextureWrap gltfConvert::getTextureWrap(int gltf_wrap){
    switch (gltf_wrap){
        case TINYGLTF_TEXTURE_WRAP_REPEAT:
            return TextureWrap::Repeat;
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            return TextureWrap::ClampToEdge;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            return TextureWrap::MirroredRepeat;
        default:
            return TextureWrap::Unknown;
    }
}

// GLwrap::Tex2Dformat gltfConvert::getImageFormat(int channels){
//     switch (channels){
//     case 1:
//         return GLwrap::Tex2Dformat::RED;
//     case 2:
//         return GLwrap::Tex2Dformat::RG;
//     case 3:
//         return GLwrap::Tex2Dformat::RGB;
//     case 4:
//         return GLwrap::Tex2Dformat::RGBA;
//     default:
//         throw std::invalid_argument("wrong channels count \"" + std::to_string(channels) + "\".");
//     }
// }

// GLuint gltfConvert::getImageWrap(int gltfConvert_wrap){
//     switch (gltfConvert_wrap){
//     case TINYGLTF_TEXTURE_WRAP_REPEAT:
//         return GL_REPEAT;
//     case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
//         return GL_CLAMP_TO_EDGE;
//     case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
//         return GL_MIRRORED_REPEAT;
//     default:
//         throw std::invalid_argument("Unknown gltfConvert_wrap \"" + std::to_string(gltfConvert_wrap) + "\".");
//     }
// }

// GLuint gltfConvert::getImageFilter(int gltfConvert_filter){
//     switch (gltfConvert_filter){
//     case TINYGLTF_TEXTURE_FILTER_LINEAR:
//         return GL_LINEAR;
//     case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
//         return GL_LINEAR_MIPMAP_LINEAR;
//     case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
//         return GL_LINEAR_MIPMAP_NEAREST;
//     case TINYGLTF_TEXTURE_FILTER_NEAREST:
//         return GL_NEAREST;
//     case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
//         return GL_NEAREST_MIPMAP_LINEAR;
//     case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
//         return GL_NEAREST_MIPMAP_NEAREST;
//     default:
//         throw std::invalid_argument("Unknown gltfConvert_filter\"" + std::to_string(gltfConvert_filter) + "\".");
//     }
// }