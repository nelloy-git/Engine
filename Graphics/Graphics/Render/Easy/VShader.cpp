#include "Graphics/Render/Easy/VShader.hpp"

using namespace Graphics::Render::Easy;

using Vertex = VShader::Vertex;

VShader::VShader() :
    Base::VShader(_getSource()){
}

const std::string &VShader::getName(VShader::UniMat4 e){
    static std::string def = "";
    static std::unordered_map<UniMat4, std::string> map {
        {UniMat4::Camera, "uni_camera"},
        {UniMat4::ModelPose, "uni_model"},
    };

    auto iter = map.find(e);
    if (iter == map.end()){
        return def;
    } else {
        return iter->second;
    };
}

const std::string &VShader::_getSource(){
    static const auto src = _createSourceAll();
    return src;
}

std::string VShader::_createInputSource(){
    int vec4_count = std::ceil((float)(sizeof(Vertex) / sizeof(float)) / 4.0);
    std::string src;

    for (int i = 0; i < vec4_count; ++i){
        auto si = std::to_string(i);
        src += "layout (location = " + si + ") in vec4 data_" + si + ";\n";
    }

    return src;
}

std::string VShader::_createParseFuncSource(const std::string &name, int n_offset, GLwrap::ElementStruct gl_size){
    static const std::vector<char> n2char {
        'x', 'y', 'z', 'w'
    };

    static const std::unordered_map<GLwrap::ElementStruct, std::string> st2string = {
        {GLwrap::ElementStruct::Scalar, "float"},
        {GLwrap::ElementStruct::Vec2, "vec2"},
        {GLwrap::ElementStruct::Vec3, "vec3"},
        {GLwrap::ElementStruct::Vec4, "vec4"},
        {GLwrap::ElementStruct::Mat3, "mat3"},
        {GLwrap::ElementStruct::Mat4, "mat4"}
    };

    std::string src
        = st2string.at(gl_size) + " " + name + "(){"
        + "return " + st2string.at(gl_size) + "(";


    int size = GLwrap::getSize(gl_size);
    int n_end = n_offset + size;
    for(int i = n_offset; i < n_end; ++i){
        int data_n = i / 4;
        int vec_n = i % 4;

        if (vec_n == 0 || i == n_offset){
            src += "data_" + std::to_string(data_n) + ".";
        }

        src += n2char[vec_n];

        if (vec_n == 3 && i != n_end - 1){
            src += ",";
        }
    }
    src += ");};\n";

    return src;
}

std::string VShader::_createParseFuncSourceAll(){
    constexpr int pos_offset = offsetof(Vertex, pos) / sizeof(float);
    constexpr int norm_offset = offsetof(Vertex, norm) / sizeof(float);
    constexpr int tang_offset = offsetof(Vertex, tang) / sizeof(float);
    constexpr int color_offset = offsetof(Vertex, color) / sizeof(float);
    constexpr int tex_coord_offset = offsetof(Vertex, tex_coord) / sizeof(float);
    constexpr int joints_offset = offsetof(Vertex, joints) / sizeof(float);
    constexpr int weights_offset = offsetof(Vertex, weights) / sizeof(float);
    constexpr int morph_offset = offsetof(Vertex, morph) / sizeof(float);

    const auto &st = VERT_STRUCT;

    std::string src;

    src += _createParseFuncSource("getPos", pos_offset, GLwrap::ElementStruct::Vec3);
    src += _createParseFuncSource("getNorm", norm_offset, GLwrap::ElementStruct::Vec3);
    src += _createParseFuncSource("getTang", tang_offset, GLwrap::ElementStruct::Vec4);

    for (int i = 0; i < st.COLOR_COUNT; ++i){
        src += _createParseFuncSource("getColor_" + std::to_string(i),
                                      color_offset + i * GLwrap::getSize(st.COLOR),
                                      st.COLOR);
    }

    for (int i = 0; i < st.TEX_COORD_COUNT; ++i){
        src += _createParseFuncSource("getTexCoord_" + std::to_string(i),
                                      tex_coord_offset + i * GLwrap::getSize(st.TEX_COORD),
                                      st.TEX_COORD);
    }

    for (int i = 0; i < st.JOINTS_COUNT; ++i){
        src += _createParseFuncSource("getJoints_" + std::to_string(i),
                                      joints_offset + i * GLwrap::getSize(st.JOINTS),
                                      st.JOINTS);
        src += _createParseFuncSource("getWeights_" + std::to_string(i),
                                      weights_offset + i * GLwrap::getSize(st.WEIGHTS),
                                      st.WEIGHTS);
    }

    for (int i = 0; i < st.MORPH_COUNT; ++i){
        src += _createParseFuncSource("getMorph_" + std::to_string(i),
                                      morph_offset + i * GLwrap::getSize(st.MORPH),
                                      st.MORPH);
    }

    return src;

}

std::string VShader::_createSourceAll(){
    std::string src = "#version 450 core\n";
    src += _createInputSource() + "\n";
    src += _createParseFuncSourceAll() + "\n";
    src += R"(
uniform mat4 uni_model;
uniform mat4 uni_camera;

out vec4 baseColor;
out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

void main(){
    gl_Position = uni_camera * uni_model * vec4(getPos(), 1.0);

    baseColor = getColor_0();
    outTexCoord_0 = getTexCoord_0();
    outTexCoord_1 = getTexCoord_1();
}
    )";

    std::cout << src.c_str();

    return src;
}
