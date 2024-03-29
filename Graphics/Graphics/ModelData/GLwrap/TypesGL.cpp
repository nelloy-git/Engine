#include "Graphics/ModelData/GLwrap/TypesGL.h"

#include "Log.h"

using namespace Graphics;

GLwrap::BufferType Draw::toGLwrap(Draw::BufferType type){
    switch (type){
        case Draw::BufferType::Index:
            return GLwrap::BufferType::IndexArray;
        case Draw::BufferType::Vertex:
            return GLwrap::BufferType::Array;
        default:
            LOG(WRN) << "unknown " << toString(type);
            return GLwrap::BufferType::Array;
    }
}

GLwrap::Type Draw::toGLwrap(Draw::BufferElemType elem_type){
    switch (elem_type){
        case Draw::BufferElemType::Byte:
            return GLwrap::Type::Byte;
        case Draw::BufferElemType::UByte:
            return GLwrap::Type::UByte;
        case Draw::BufferElemType::Short:
            return GLwrap::Type::Short;
        case Draw::BufferElemType::UShort:
            return GLwrap::Type::UShort;
        case Draw::BufferElemType::Int:
            return GLwrap::Type::Int;
        case Draw::BufferElemType::UInt:
            return GLwrap::Type::UInt;
        case Draw::BufferElemType::Float:
            return GLwrap::Type::Float;
        case Draw::BufferElemType::Double:
            return GLwrap::Type::Double;
        default:
            LOG(WRN) << "unknown " << toString(elem_type);
            return GLwrap::Type::Byte;
    }
}

GLwrap::Size Draw::toGLwrap(Draw::BufferElemStruct elem_struct){
    switch(elem_struct){
        case Draw::BufferElemStruct::Scalar:
            return GLwrap::Size::Scalar;
        case Draw::BufferElemStruct::Vec2:
            return GLwrap::Size::Vec2;
        case Draw::BufferElemStruct::Vec3:
            return GLwrap::Size::Vec3;
        case Draw::BufferElemStruct::Vec4:
            return GLwrap::Size::Vec4;
        case Draw::BufferElemStruct::Mat2:
            return GLwrap::Size::Mat2;
        case Draw::BufferElemStruct::Mat3:
            return GLwrap::Size::Mat3;
        case Draw::BufferElemStruct::Mat4:
            return GLwrap::Size::Mat4;
        default:
            LOG(WRN) << "unknown " << toString(elem_struct);
            return GLwrap::Size::Scalar;
    }
}

GLwrap::Tex2DPixelFormat Draw::toGLwrap(Draw::TextureFormat fmt){
    switch (fmt){
        case Draw::TextureFormat::RED:
            return GLwrap::Tex2DPixelFormat::RED;
        case Draw::TextureFormat::RG:
            return GLwrap::Tex2DPixelFormat::RG;
        case Draw::TextureFormat::RGB:
            return GLwrap::Tex2DPixelFormat::RGB;
        case Draw::TextureFormat::RGBA:
            return GLwrap::Tex2DPixelFormat::RGBA;
        default:
            LOG(WRN) << "unknown " << toString(fmt);
            return GLwrap::Tex2DPixelFormat::RGBA;
    }
}

GLwrap::Tex2DWrap Draw::toGLwrap(Draw::TextureWrap wrap){
    switch (wrap){
        case Draw::TextureWrap::Repeat:
            return GLwrap::Tex2DWrap::Repeat;
        case Draw::TextureWrap::ClampToEdge:
            return GLwrap::Tex2DWrap::ClampToEdge;
        case Draw::TextureWrap::MirroredRepeat:
            return GLwrap::Tex2DWrap::MirroredRepeat;
        default:
            LOG(WRN) << "unknown " << toString(wrap);
            return GLwrap::Tex2DWrap::Repeat;
    }
}

GLwrap::Tex2DFilter Draw::toGLwrap(Draw::TextureFilter filter){
    switch (filter){
        case Draw::TextureFilter::Linear:
            return GLwrap::Tex2DFilter::Linear;
        case Draw::TextureFilter::LinearMipmapLinear:
            return GLwrap::Tex2DFilter::LinearMipmapLinear;
        case Draw::TextureFilter::LinearMipmapNearest:
            return GLwrap::Tex2DFilter::LinearMipmapNearest;
        case Draw::TextureFilter::Nearest:
            return GLwrap::Tex2DFilter::Nearest;
        case Draw::TextureFilter::NearestMipmapLinear:
            return GLwrap::Tex2DFilter::NearestMipmapLinear;
        case Draw::TextureFilter::NearestMipmapNearest:
            return GLwrap::Tex2DFilter::NearestMipmapNearest;
        default:
            LOG(WRN) << "unknown " << toString(filter);
            return GLwrap::Tex2DFilter::Linear;
    }
}

GLwrap::DrawMode Draw::toGLwrap(Draw::PrimitiveDrawMode mode){
    switch (mode){
        case Draw::PrimitiveDrawMode::Points:
            return GLwrap::DrawMode::Points;
        case Draw::PrimitiveDrawMode::Line:
            return GLwrap::DrawMode::Line;
        case Draw::PrimitiveDrawMode::LineLoop:
            return GLwrap::DrawMode::LineLoop;
        case Draw::PrimitiveDrawMode::LineStrip:
            return GLwrap::DrawMode::LineStrip;
        case Draw::PrimitiveDrawMode::Triangles:
            return GLwrap::DrawMode::Triangles;
        case Draw::PrimitiveDrawMode::TriangleFan:
            return GLwrap::DrawMode::TriangleFan;
        case Draw::PrimitiveDrawMode::TriangleStrip:
            return GLwrap::DrawMode::TriangleStrip;
        default:
            LOG(WRN) << "unknown " << toString(mode);
            return GLwrap::DrawMode::Line;
    }
}