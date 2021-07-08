#include "Model/GLwrap/TypesGLwrap.h"

#include "Log.h"

using namespace Graphics;

constexpr inline GLwrap::BufferType Model::toGLwrap(Model::BufferType type){
    switch (type){
        case Model::BufferType::Index:
            return GLwrap::BufferType::IndexArray;
        case Model::BufferType::Vertex:
            return GLwrap::BufferType::Array;
        default:
            LOG(WRN) << "unknown " << toString(type);
            return GLwrap::BufferType::Array;
    }
}

constexpr inline GLwrap::ElementType Model::toGLwrap(Model::BufferElemType elem_type){
    switch (elem_type){
        case Model::BufferElemType::Byte:
            return GLwrap::ElementType::Byte;
        case Model::BufferElemType::UByte:
            return GLwrap::ElementType::UByte;
        case Model::BufferElemType::Short:
            return GLwrap::ElementType::Short;
        case Model::BufferElemType::UShort:
            return GLwrap::ElementType::UShort;
        case Model::BufferElemType::Int:
            return GLwrap::ElementType::Int;
        case Model::BufferElemType::UInt:
            return GLwrap::ElementType::UInt;
        case Model::BufferElemType::Float:
            return GLwrap::ElementType::Float;
        case Model::BufferElemType::Double:
            return GLwrap::ElementType::Double;
        default:
            LOG(WRN) << "unknown " << toString(elem_type);
            return GLwrap::ElementType::Byte;
    }
}

constexpr inline GLwrap::ElementStruct Model::toGLwrap(Model::BufferElemStruct elem_struct){
    switch(elem_struct){
        case Model::BufferElemStruct::Scalar:
            return GLwrap::ElementStruct::Scalar;
        case Model::BufferElemStruct::Vec2:
            return GLwrap::ElementStruct::Vec2;
        case Model::BufferElemStruct::Vec3:
            return GLwrap::ElementStruct::Vec3;
        case Model::BufferElemStruct::Vec4:
            return GLwrap::ElementStruct::Vec4;
        case Model::BufferElemStruct::Mat2:
            return GLwrap::ElementStruct::Mat2;
        case Model::BufferElemStruct::Mat3:
            return GLwrap::ElementStruct::Mat3;
        case Model::BufferElemStruct::Mat4:
            return GLwrap::ElementStruct::Mat4;
        default:
            LOG(WRN) << "unknown " << toString(elem_struct);
            return GLwrap::ElementStruct::Scalar;
    }
}

constexpr inline GLwrap::Tex2DPixelFormat Model::toGLwrap(Model::TextureFormat fmt){
    switch (fmt){
        case Model::TextureFormat::RED:
            return GLwrap::Tex2DPixelFormat::RED;
        case Model::TextureFormat::RG:
            return GLwrap::Tex2DPixelFormat::RG;
        case Model::TextureFormat::RGB:
            return GLwrap::Tex2DPixelFormat::RGB;
        case Model::TextureFormat::RGBA:
            return GLwrap::Tex2DPixelFormat::RGBA;
        default:
            LOG(WRN) << "unknown " << toString(fmt);
            return GLwrap::Tex2DPixelFormat::RGBA;
    }
}

constexpr inline GLwrap::Tex2DWrap Model::toGLwrap(Model::TextureWrap wrap){
    switch (wrap){
        case Model::TextureWrap::Repeat:
            return GLwrap::Tex2DWrap::Repeat;
        case Model::TextureWrap::ClampToEdge:
            return GLwrap::Tex2DWrap::ClampToEdge;
        case Model::TextureWrap::MirroredRepeat:
            return GLwrap::Tex2DWrap::MirroredRepeat;
        default:
            LOG(WRN) << "unknown " << toString(wrap);
            return GLwrap::Tex2DWrap::Repeat;
    }
}

constexpr inline GLwrap::Tex2DFilter Model::toGLwrap(Model::TextureFilter filter){
    switch (filter){
        case Model::TextureFilter::Linear:
            return GLwrap::Tex2DFilter::Linear;
        case Model::TextureFilter::LinearMipmapLinear:
            return GLwrap::Tex2DFilter::LinearMipmapLinear;
        case Model::TextureFilter::LinearMipmapNearest:
            return GLwrap::Tex2DFilter::LinearMipmapNearest;
        case Model::TextureFilter::Nearest:
            return GLwrap::Tex2DFilter::Nearest;
        case Model::TextureFilter::NearestMipmapLinear:
            return GLwrap::Tex2DFilter::NearestMipmapLinear;
        case Model::TextureFilter::NearestMipmapNearest:
            return GLwrap::Tex2DFilter::NearestMipmapNearest;
        default:
            LOG(WRN) << "unknown " << toString(filter);
            return GLwrap::Tex2DFilter::Linear;
    }
}

constexpr inline GLwrap::DrawMode Model::toGLwrap(Model::PrimitiveDrawMode mode){
    switch (mode){
        case Model::PrimitiveDrawMode::Points:
            return GLwrap::DrawMode::Points;
        case Model::PrimitiveDrawMode::Line:
            return GLwrap::DrawMode::Line;
        case Model::PrimitiveDrawMode::LineLoop:
            return GLwrap::DrawMode::LineLoop;
        case Model::PrimitiveDrawMode::LineStrip:
            return GLwrap::DrawMode::LineStrip;
        case Model::PrimitiveDrawMode::Triangles:
            return GLwrap::DrawMode::Triangles;
        case Model::PrimitiveDrawMode::TriangleFan:
            return GLwrap::DrawMode::TriangleFan;
        case Model::PrimitiveDrawMode::TriangleStrip:
            return GLwrap::DrawMode::TriangleStrip;
        default:
            LOG(WRN) << "unknown " << toString(mode);
            return GLwrap::DrawMode::Line;
    }
}