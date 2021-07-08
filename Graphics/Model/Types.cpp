#include "Model/Types.h"

using namespace Graphics;

const char *Model::toString(Model::BufferType type){
    switch (type){
        case Model::BufferType::Vertex:
            return "BufferType::Vertex";
        case Model::BufferType::Index:
            return "BufferType::Index";
        default:
            return "BufferType::Other";
    }
}

const char *Model::toString(Model::BufferElemType elem_type){
    switch (elem_type){
        case Model::BufferElemType::Byte:
            return "BufferElemType::Byte";
        case Model::BufferElemType::UByte:
            return "BufferElemType::UByte";
        case Model::BufferElemType::Short:
            return "BufferElemType::Short";
        case Model::BufferElemType::UShort:
            return "BufferElemType::UShort";
        case Model::BufferElemType::Int:
            return "BufferElemType::Int";
        case Model::BufferElemType::UInt:
            return "BufferElemType::UInt";
        case Model::BufferElemType::Float:
            return "BufferElemType::Float";
        case Model::BufferElemType::Double:
            return "BufferElemType::Double";
        default:
            return "BufferElemType::Unknown";
    }
}

unsigned int Model::getSize(BufferElemType elem_type){
    switch (elem_type){
        case Model::BufferElemType::Byte:
            return sizeof(char);
        case Model::BufferElemType::UByte:
            return sizeof(unsigned char);
        case Model::BufferElemType::Short:
            return sizeof(short);
        case Model::BufferElemType::UShort:
            return sizeof(unsigned short);
        case Model::BufferElemType::Int:
            return sizeof(int);
        case Model::BufferElemType::UInt:
            return sizeof(unsigned int);
        case Model::BufferElemType::Float:
            return sizeof(float);
        case Model::BufferElemType::Double:
            return sizeof(double);
        default:
            return 0;
    }
}

unsigned int Model::getSize(BufferElemStruct elem_struct){
    switch (elem_struct){
        case Model::BufferElemStruct::Scalar:
            return 1;
        case Model::BufferElemStruct::Vec2:
            return 2;
        case Model::BufferElemStruct::Vec3:
            return 3;
        case Model::BufferElemStruct::Vec4:
            return 4;
        case Model::BufferElemStruct::Mat2:
            return 4;
        case Model::BufferElemStruct::Mat3:
            return 9;
        case Model::BufferElemStruct::Mat4:
            return 16;
        default:
            return 0;
    }
}

const char *Model::toString(Model::BufferElemStruct elem_struct){
    switch (elem_struct){
        case Model::BufferElemStruct::Scalar:
            return "BufferElemStruct::Scalar";
        case Model::BufferElemStruct::Vec2:
            return "BufferElemStruct::Vec2";
        case Model::BufferElemStruct::Vec3:
            return "BufferElemStruct::Vec3";
        case Model::BufferElemStruct::Vec4:
            return "BufferElemStruct::Vec4";
        case Model::BufferElemStruct::Mat2:
            return "BufferElemStruct::Mat2";
        case Model::BufferElemStruct::Mat3:
            return "BufferElemStruct::Mat3";
        case Model::BufferElemStruct::Mat4:
            return "BufferElemStruct::Mat4";
        default:
            return "BufferElemStruct::Unknown";
    }
}

const char *Model::toString(Model::PrimitiveDrawMode mode){
    switch (mode){
        case Model::PrimitiveDrawMode::Points:
            return "PrimitiveDrawMode::Points";
        case Model::PrimitiveDrawMode::Line:
            return "PrimitiveDrawMode::Line";
        case Model::PrimitiveDrawMode::LineLoop:
            return "PrimitiveDrawMode::LineLoop";
        case Model::PrimitiveDrawMode::LineStrip:
            return "PrimitiveDrawMode::LineStrip";
        case Model::PrimitiveDrawMode::Triangles:
            return "PrimitiveDrawMode::Triangles";
        case Model::PrimitiveDrawMode::TriangleStrip:
            return "PrimitiveDrawMode::TrianglesStrip";
        case Model::PrimitiveDrawMode::TriangleFan:
            return "PrimitiveDrawMode::TrianglesFan";
        default:
            return "PrimitiveDrawMode::Unknown";
    }
}

const char *Model::toString(Model::PrimitiveAttribute attr){
    switch (attr){
        case Model::PrimitiveAttribute::Position:
            return "PrimitiveAttribute::Position";
        case Model::PrimitiveAttribute::Normal:
            return "PrimitiveAttribute::Normal";
        case Model::PrimitiveAttribute::Tangent:
            return "PrimitiveAttribute::Tangent";
        case Model::PrimitiveAttribute::TexCoord_0:
            return "PrimitiveAttribute::TexCoord_0";
        case Model::PrimitiveAttribute::TexCoord_1:
            return "PrimitiveAttribute::TexCoord_1";
        case Model::PrimitiveAttribute::Color_0:
            return "PrimitiveAttribute::Color_0";
        case Model::PrimitiveAttribute::Joints_0:
            return "PrimitiveAttribute::Joints_0";
        case Model::PrimitiveAttribute::Joints_1:
            return "PrimitiveAttribute::Joints_1";
        case Model::PrimitiveAttribute::Weights_0:
            return "PrimitiveAttribute::Weights_0";
        case Model::PrimitiveAttribute::Weights_1:
            return "PrimitiveAttribute::Weights_1";
        default:
            return "PrimitiveAttribute::Unknown";
    }
}

int Model::getLocation(Model::PrimitiveAttribute attr){
    switch (attr){
        case Model::PrimitiveAttribute::Position:
            return 0;
        case Model::PrimitiveAttribute::Normal:
            return 1;
        case Model::PrimitiveAttribute::Tangent:
            return 2;
        case Model::PrimitiveAttribute::TexCoord_0:
            return 3;
        case Model::PrimitiveAttribute::TexCoord_1:
            return 4;
        case Model::PrimitiveAttribute::Color_0:
            return 5;
        case Model::PrimitiveAttribute::Joints_0:
            return 6;
        case Model::PrimitiveAttribute::Joints_1:
            return 7;
        case Model::PrimitiveAttribute::Weights_0:
            return 8;
        case Model::PrimitiveAttribute::Weights_1:
            return 9;
        default:
            return -1;
    }
};

int Model::getMorphTargetLocation(int target, PrimitiveAttribute attr){
    int base = 10 + 3 * target;

    // Based on getLocation.
    switch (attr){
        case Model::PrimitiveAttribute::Position:
            return base;
        case Model::PrimitiveAttribute::Normal:
            return base + 1;
        case Model::PrimitiveAttribute::Tangent:
            return base + 2;
        default:
            return -1;
    }
}

const char *Model::toString(Model::TextureFormat fmt){
    switch (fmt){
        case Model::TextureFormat::RED:
            return "TextureFormat::RED";
        case Model::TextureFormat::RG:
            return "TextureFormat::RG";
        case Model::TextureFormat::RGB:
            return "TextureFormat::RGB";
        case Model::TextureFormat::RGBA:
            return "TextureFormat::RGBA";
        default:
            return "TextureFormat::Unknown";
    }
}

const char *Model::toString(Model::TextureWrap wrap){
    switch (wrap){
        case Model::TextureWrap::Repeat:
            return "TextureWrap::Repeat";
        case Model::TextureWrap::ClampToEdge:
            return "TextureWrap::ClampToEdge";
        case Model::TextureWrap::MirroredRepeat:
            return "TextureWrap::MirroredRepeat";
        default:
            return "TextureWrap::Unknown";
    }
}

const char *Model::toString(Model::TextureFilter filter){
    switch (filter){
        case Model::TextureFilter::Linear:
            return "TextureFilter::Linear";
        case Model::TextureFilter::LinearMipmapLinear:
            return "TextureFilter::LinearMipmapLinear";
        case Model::TextureFilter::LinearMipmapNearest:
            return "TextureFilter::LinearMipmapNearest";
        case Model::TextureFilter::Nearest:
            return "TextureFilter::Nearest";
        case Model::TextureFilter::NearestMipmapLinear:
            return "TextureFilter::NearestMipmapLinear";
        case Model::TextureFilter::NearestMipmapNearest:
            return "TextureFilter::NearestMipmapNearest";
        default:
            return "TextureFilter::Unknown";
    }
}