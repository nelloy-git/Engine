#include "Graphics/Model/Loader/TinyGltf/Types.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace Graphics::Model;

GLwrap::DrawMode gltf::getDrawMode(const tinygltf::Primitive &prim){
    switch (prim.mode){
        case TINYGLTF_MODE_POINTS:
            return GLwrap::DrawMode::Points;
        case TINYGLTF_MODE_LINE:
            return GLwrap::DrawMode::Line;
        case TINYGLTF_MODE_LINE_LOOP:
            return GLwrap::DrawMode::LineLoop;
        case TINYGLTF_MODE_LINE_STRIP:
            return GLwrap::DrawMode::LineStrip;
        case TINYGLTF_MODE_TRIANGLES:
            return GLwrap::DrawMode::Triangles;
        case TINYGLTF_MODE_TRIANGLE_STRIP:
            return GLwrap::DrawMode::TriangleStrip;
        case TINYGLTF_MODE_TRIANGLE_FAN:
            return GLwrap::DrawMode::TriangleFan;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::DrawMode");
    }
}

GLwrap::ElementType gltf::getElemType(const tinygltf::Accessor &acc){
    switch (acc.componentType){
        case TINYGLTF_COMPONENT_TYPE_BYTE:
            return GLwrap::ElementType::Byte;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            return GLwrap::ElementType::UByte;
        case TINYGLTF_COMPONENT_TYPE_SHORT:
            return GLwrap::ElementType::Short;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            return GLwrap::ElementType::UShort;
        case TINYGLTF_COMPONENT_TYPE_INT:
            return GLwrap::ElementType::Int;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            return GLwrap::ElementType::UInt;
        case TINYGLTF_COMPONENT_TYPE_FLOAT:
            return GLwrap::ElementType::Float;
        case TINYGLTF_COMPONENT_TYPE_DOUBLE:
            return GLwrap::ElementType::Double;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::ElementType");
    }
}

GLwrap::ElementStruct gltf::getElemStruct(const tinygltf::Accessor &acc){
    switch (acc.type){
        case TINYGLTF_TYPE_SCALAR:
            return GLwrap::ElementStruct::Scalar;
        case TINYGLTF_TYPE_VEC2:
            return GLwrap::ElementStruct::Vec2;
        case TINYGLTF_TYPE_VEC3:
            return GLwrap::ElementStruct::Vec3;
        case TINYGLTF_TYPE_VEC4:
            return GLwrap::ElementStruct::Vec4;
        case TINYGLTF_TYPE_MAT2:
            return GLwrap::ElementStruct::Vec4;
        case TINYGLTF_TYPE_MAT3:
            return GLwrap::ElementStruct::Mat3;
        case TINYGLTF_TYPE_MAT4:
            return GLwrap::ElementStruct::Mat4;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::ElementStruct");
    }
}

GLwrap::Tex2DFilter gltf::getMinFilter(const tinygltf::Sampler &sampler){
    switch (sampler.minFilter){
        case TINYGLTF_TEXTURE_FILTER_LINEAR: 
            return GLwrap::Tex2DFilter::Linear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: 
            return GLwrap::Tex2DFilter::LinearMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: 
            return GLwrap::Tex2DFilter::LinearMipmapNearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST: 
            return GLwrap::Tex2DFilter::Nearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: 
            return GLwrap::Tex2DFilter::NearestMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: 
            return GLwrap::Tex2DFilter::NearestMipmapNearest;
        default:
            return GLwrap::Tex2DFilter::Linear;
    }
}

GLwrap::Tex2DFilter gltf::getMagFilter(const tinygltf::Sampler &sampler){
    switch (sampler.magFilter){
        case TINYGLTF_TEXTURE_FILTER_LINEAR: 
            return GLwrap::Tex2DFilter::Linear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: 
            return GLwrap::Tex2DFilter::LinearMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST: 
            return GLwrap::Tex2DFilter::LinearMipmapNearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST: 
            return GLwrap::Tex2DFilter::Nearest;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR: 
            return GLwrap::Tex2DFilter::NearestMipmapLinear;
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST: 
            return GLwrap::Tex2DFilter::NearestMipmapNearest;
        default:
            return GLwrap::Tex2DFilter::Linear;
    }
}

GLwrap::Tex2DWrap gltf::getWrapS(const tinygltf::Sampler &sampler){
    switch (sampler.wrapS){
        case TINYGLTF_TEXTURE_WRAP_REPEAT:
            return GLwrap::Tex2DWrap::Repeat;
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            return GLwrap::Tex2DWrap::ClampToEdge;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            return GLwrap::Tex2DWrap::MirroredRepeat;
        default:
            return GLwrap::Tex2DWrap::Repeat;
    }
}

GLwrap::Tex2DWrap gltf::getWrapT(const tinygltf::Sampler &sampler){
    switch (sampler.wrapT){
        case TINYGLTF_TEXTURE_WRAP_REPEAT:
            return GLwrap::Tex2DWrap::Repeat;
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            return GLwrap::Tex2DWrap::ClampToEdge;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            return GLwrap::Tex2DWrap::MirroredRepeat;
        default:
            return GLwrap::Tex2DWrap::Repeat;
    }
}

GLwrap::Tex2DInternalFormat gltf::getInternalFormat(const tinygltf::Image &image){
    switch (image.component){
        case 1:
            return GLwrap::Tex2DInternalFormat::RED;
        case 2:
            return GLwrap::Tex2DInternalFormat::RG;
        case 3:
            return GLwrap::Tex2DInternalFormat::RGB;
        case 4:
            return GLwrap::Tex2DInternalFormat::RGBA;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::Tex2DInternalFormat");
    }
}

GLwrap::Tex2DPixelFormat gltf::getPixelFormat(const tinygltf::Image &image){
    switch (image.component){
        case 1:
            return GLwrap::Tex2DPixelFormat::RED;
        case 2:
            return GLwrap::Tex2DPixelFormat::RG;
        case 3:
            return GLwrap::Tex2DPixelFormat::RGB;
        case 4:
            return GLwrap::Tex2DPixelFormat::RGBA;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::Tex2DPixelFormat");
    }
}

GLwrap::Tex2DPixelType gltf::getPixelType(const tinygltf::Image &image){
    switch (image.bits){
        case 8 * sizeof(char):
            return GLwrap::Tex2DPixelType::UNSIGNED_BYTE;
        case 8 * sizeof(short int):
            return GLwrap::Tex2DPixelType::UNSIGNED_SHORT;
        case 8 * sizeof(int):
            return GLwrap::Tex2DPixelType::UNSIGNED_INT;
        default:
            gltf::detailed::throwErr("Unknown GLwrap::Tex2DPixelType");
    }
}