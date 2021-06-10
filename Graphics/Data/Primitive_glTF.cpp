#include "Data/Primitive_glTF.h"

#include <memory>

#include "Utils/Log.h"

using namespace Graphics;
using namespace GLwrap;



Primitive_glTF::Primitive_glTF(const tinygltf::Model &model,
                               const tinygltf::Primitive &primitive){

    __loadAttributes(model, primitive);
    __loadElements(model, primitive);
    __loadVAO();
}

Primitive_glTF::~Primitive_glTF(){

}

void Primitive_glTF::draw(){
    __vao->draw(__draw_mode, __vertices, __indices_type, __indices_offset);
}

int __getAttrLoc(const std::string &name){
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

GLwrap::ShaderDataSize __getAttrComponentSize(int glTF_component_size){
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

GLwrap::ShaderDataType __getAttrComponentType(int glFT_component_type){
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

GLwrap::VAOdrawMode __getDrawMode(int glTF_draw_mode){
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

void Primitive_glTF::__loadAttributes(const tinygltf::Model &model, const tinygltf::Primitive &primitive){

    for (auto &attrib_data : primitive.attributes) {
        const tinygltf::Accessor &accessor = model.accessors[attrib_data.second];
        const tinygltf::BufferView &buffer_view = model.bufferViews[accessor.bufferView];
        const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];

        auto vbo = std::make_shared<GLwrap::VBO>(buffer_view.byteLength);
        vbo->load(&buffer.data.at(0), buffer_view.byteOffset);

        auto attr_loc = __getAttrLoc(attrib_data.first);
        if (attr_loc < 0){
            LOG(WRN) << "unknown attribute \"" << attrib_data.first << "\n";
            continue;
        }

        auto attr_size = __getAttrComponentSize(accessor.componentType);
        auto attr_type = __getAttrComponentType(accessor.componentType);

        __attributes.push_back(std::make_shared<GLwrap::BufferAttrubute>(
            vbo,
            attr_loc,
            attr_size,
            attr_type,
            accessor.normalized,
            accessor.ByteStride(buffer_view),
            accessor.byteOffset
        ));
    }
}

void Primitive_glTF::__loadVAO(){
    __vao = std::make_shared<GLwrap::VAO>();
    __vao->load(__attributes, __veo);
}

void Primitive_glTF::__loadElements(const tinygltf::Model &model, const tinygltf::Primitive &primitive){
    const tinygltf::Accessor &accessor = model.accessors[primitive.indices];
    const tinygltf::BufferView &buffer_view = model.bufferViews[accessor.bufferView];
    const tinygltf::Buffer &buffer = model.buffers[buffer_view.buffer];

    __vertices = accessor.count;
    __draw_mode = __getDrawMode(primitive.mode);
    __indices_type = __getAttrComponentType(accessor.componentType);
    __indices_offset = accessor.byteOffset;
    __veo = std::make_shared<GLwrap::VEO>(bufTINYfer_view.byteLength);
    __veo->load(&buffer.data.at(0), buffer_view.byteOffset);
}