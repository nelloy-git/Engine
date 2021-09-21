#include "Graphics/Model/Loader/TinyGltf/Types.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace Graphics::Model;

GLwrap::BufferType gltf::toBufferType(int type){
    switch (type){
        case TINYGLTF_TARGET_ARRAY_BUFFER:
            return GLwrap::BufferType::Array;
        case TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER:
            return GLwrap::BufferType::IndexArray;
        default:
           return GLwrap::BufferType::Unknown;
    }
}

GLwrap::DrawMode gltf::toDrawMode(int mode){
    switch (mode){
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
            return GLwrap::DrawMode::Unknown;
    }
}

GLwrap::ElementType gltf::toElemType(int elem_type){
    switch (elem_type){
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
            throw GLwrap::ElementType::Unknown;
    }
}

GLwrap::ElementStruct gltf::toElemStruct(int elem_struct){
    switch (elem_struct){
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
            return GLwrap::ElementStruct::Unknown;
    }
}

GLwrap::Tex2DFilter gltf::toTextureFilter(int filter){
    switch (filter){
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
            return GLwrap::Tex2DFilter::Unknown;
    }
}

GLwrap::Tex2DWrap gltf::toTextureWrap(int wrap){
    switch (wrap){
        case TINYGLTF_TEXTURE_WRAP_REPEAT:
            return GLwrap::Tex2DWrap::Repeat;
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            return GLwrap::Tex2DWrap::ClampToEdge;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            return GLwrap::Tex2DWrap::MirroredRepeat;
        default:
            return GLwrap::Tex2DWrap::Unknown;
    }
}