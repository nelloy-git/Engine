#include "Draw/Types.h"

using namespace Graphics;

const char *Draw::toString(Draw::BufferType type){
    switch (type){
        case Draw::BufferType::Vertex:
            return "BufferType::Vertex";
        case Draw::BufferType::Index:
            return "BufferType::Index";
        default:
            return "BufferType::Other";
    }
}

const char *Draw::toString(Draw::BufferElemType elem_type){
    switch (elem_type){
        case Draw::BufferElemType::Byte:
            return "BufferElemType::Byte";
        case Draw::BufferElemType::UByte:
            return "BufferElemType::UByte";
        case Draw::BufferElemType::Short:
            return "BufferElemType::Short";
        case Draw::BufferElemType::UShort:
            return "BufferElemType::UShort";
        case Draw::BufferElemType::Int:
            return "BufferElemType::Int";
        case Draw::BufferElemType::UInt:
            return "BufferElemType::UInt";
        case Draw::BufferElemType::Float:
            return "BufferElemType::Float";
        case Draw::BufferElemType::Double:
            return "BufferElemType::Double";
        default:
            return "BufferElemType::Unknown";
    }
}

unsigned int Draw::getSize(BufferElemType elem_type){
    switch (elem_type){
        case Draw::BufferElemType::Byte:
            return sizeof(char);
        case Draw::BufferElemType::UByte:
            return sizeof(unsigned char);
        case Draw::BufferElemType::Short:
            return sizeof(short);
        case Draw::BufferElemType::UShort:
            return sizeof(unsigned short);
        case Draw::BufferElemType::Int:
            return sizeof(int);
        case Draw::BufferElemType::UInt:
            return sizeof(unsigned int);
        case Draw::BufferElemType::Float:
            return sizeof(float);
        case Draw::BufferElemType::Double:
            return sizeof(double);
        default:
            return 0;
    }
}

unsigned int Draw::getSize(BufferElemStruct elem_struct){
    switch (elem_struct){
        case Draw::BufferElemStruct::Scalar:
            return 1;
        case Draw::BufferElemStruct::Vec2:
            return 2;
        case Draw::BufferElemStruct::Vec3:
            return 3;
        case Draw::BufferElemStruct::Vec4:
            return 4;
        case Draw::BufferElemStruct::Mat2:
            return 4;
        case Draw::BufferElemStruct::Mat3:
            return 9;
        case Draw::BufferElemStruct::Mat4:
            return 16;
        default:
            return 0;
    }
}

const char *Draw::toString(Draw::BufferElemStruct elem_struct){
    switch (elem_struct){
        case Draw::BufferElemStruct::Scalar:
            return "BufferElemStruct::Scalar";
        case Draw::BufferElemStruct::Vec2:
            return "BufferElemStruct::Vec2";
        case Draw::BufferElemStruct::Vec3:
            return "BufferElemStruct::Vec3";
        case Draw::BufferElemStruct::Vec4:
            return "BufferElemStruct::Vec4";
        case Draw::BufferElemStruct::Mat2:
            return "BufferElemStruct::Mat2";
        case Draw::BufferElemStruct::Mat3:
            return "BufferElemStruct::Mat3";
        case Draw::BufferElemStruct::Mat4:
            return "BufferElemStruct::Mat4";
        default:
            return "BufferElemStruct::Unknown";
    }
}

const char *Draw::toString(Draw::PrimitiveDrawMode mode){
    switch (mode){
        case Draw::PrimitiveDrawMode::Points:
            return "PrimitiveDrawMode::Points";
        case Draw::PrimitiveDrawMode::Line:
            return "PrimitiveDrawMode::Line";
        case Draw::PrimitiveDrawMode::LineLoop:
            return "PrimitiveDrawMode::LineLoop";
        case Draw::PrimitiveDrawMode::LineStrip:
            return "PrimitiveDrawMode::LineStrip";
        case Draw::PrimitiveDrawMode::Triangles:
            return "PrimitiveDrawMode::Triangles";
        case Draw::PrimitiveDrawMode::TriangleStrip:
            return "PrimitiveDrawMode::TrianglesStrip";
        case Draw::PrimitiveDrawMode::TriangleFan:
            return "PrimitiveDrawMode::TrianglesFan";
        default:
            return "PrimitiveDrawMode::Unknown";
    }
}

const char *Draw::toString(Draw::PrimitiveAttribute attr){
    switch (attr){
        case Draw::PrimitiveAttribute::Position:
            return "PrimitiveAttribute::Position";
        case Draw::PrimitiveAttribute::Normal:
            return "PrimitiveAttribute::Normal";
        case Draw::PrimitiveAttribute::Tangent:
            return "PrimitiveAttribute::Tangent";
        case Draw::PrimitiveAttribute::TexCoord_0:
            return "PrimitiveAttribute::TexCoord_0";
        case Draw::PrimitiveAttribute::TexCoord_1:
            return "PrimitiveAttribute::TexCoord_1";
        case Draw::PrimitiveAttribute::Color_0:
            return "PrimitiveAttribute::Color_0";
        case Draw::PrimitiveAttribute::Joints_0:
            return "PrimitiveAttribute::Joints_0";
        case Draw::PrimitiveAttribute::Joints_1:
            return "PrimitiveAttribute::Joints_1";
        case Draw::PrimitiveAttribute::Weights_0:
            return "PrimitiveAttribute::Weights_0";
        case Draw::PrimitiveAttribute::Weights_1:
            return "PrimitiveAttribute::Weights_1";
        default:
            return "PrimitiveAttribute::Unknown";
    }
}

int Draw::getLocation(Draw::PrimitiveAttribute attr){
    switch (attr){
        case Draw::PrimitiveAttribute::Position:
            return 0;
        case Draw::PrimitiveAttribute::Normal:
            return 1;
        case Draw::PrimitiveAttribute::Tangent:
            return 2;
        case Draw::PrimitiveAttribute::TexCoord_0:
            return 3;
        case Draw::PrimitiveAttribute::TexCoord_1:
            return 4;
        case Draw::PrimitiveAttribute::Color_0:
            return 5;
        case Draw::PrimitiveAttribute::Joints_0:
            return 6;
        case Draw::PrimitiveAttribute::Joints_1:
            return 7;
        case Draw::PrimitiveAttribute::Weights_0:
            return 8;
        case Draw::PrimitiveAttribute::Weights_1:
            return 9;
        default:
            return -1;
    }
};

int Draw::getMorphTargetLocation(int target, PrimitiveAttribute attr){
    int base = 10 + 3 * target;

    // Based on getLocation.
    switch (attr){
        case Draw::PrimitiveAttribute::Position:
            return base;
        case Draw::PrimitiveAttribute::Normal:
            return base + 1;
        case Draw::PrimitiveAttribute::Tangent:
            return base + 2;
        default:
            return -1;
    }
}

const char *Draw::toString(Draw::TextureFormat fmt){
    switch (fmt){
        case Draw::TextureFormat::RED:
            return "TextureFormat::RED";
        case Draw::TextureFormat::RG:
            return "TextureFormat::RG";
        case Draw::TextureFormat::RGB:
            return "TextureFormat::RGB";
        case Draw::TextureFormat::RGBA:
            return "TextureFormat::RGBA";
        default:
            return "TextureFormat::Unknown";
    }
}

const char *Draw::toString(Draw::TextureWrap wrap){
    switch (wrap){
        case Draw::TextureWrap::Repeat:
            return "TextureWrap::Repeat";
        case Draw::TextureWrap::ClampToEdge:
            return "TextureWrap::ClampToEdge";
        case Draw::TextureWrap::MirroredRepeat:
            return "TextureWrap::MirroredRepeat";
        default:
            return "TextureWrap::Unknown";
    }
}

const char *Draw::toString(Draw::TextureFilter filter){
    switch (filter){
        case Draw::TextureFilter::Linear:
            return "TextureFilter::Linear";
        case Draw::TextureFilter::LinearMipmapLinear:
            return "TextureFilter::LinearMipmapLinear";
        case Draw::TextureFilter::LinearMipmapNearest:
            return "TextureFilter::LinearMipmapNearest";
        case Draw::TextureFilter::Nearest:
            return "TextureFilter::Nearest";
        case Draw::TextureFilter::NearestMipmapLinear:
            return "TextureFilter::NearestMipmapLinear";
        case Draw::TextureFilter::NearestMipmapNearest:
            return "TextureFilter::NearestMipmapNearest";
        default:
            return "TextureFilter::Unknown";
    }
}