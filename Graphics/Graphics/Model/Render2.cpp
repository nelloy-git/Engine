#include "Graphics/Model/Render.hpp"

#include <iostream>

using namespace Graphics::Model;

using Vertex = Render::Vertex;
using Primitive = Render::Primitive;
using VShader = Graphics::Render::Base::VShader;
using FShader = Graphics::Render::Base::FShader;
using Renderer = Render::Renderer;

static std::string createInputSource(){
    int vec4_count = std::ceil((float)(sizeof(Vertex) / sizeof(float)) / 4.0);
    std::string src;

    for (int i = 0; i < vec4_count; ++i){
        auto si = std::to_string(i);
        src += "layout (location = " + si + ") in vec4 data_" + si + ";\n";
    }

    return src;
}

static std::string createParseFuncSource(const std::string &name, int n_offset, GLwrap::ElementStruct gl_size){
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

static std::string createParseFuncSourceAll(){
    constexpr int pos_offset = offsetof(Vertex, pos) / sizeof(float);
    constexpr int norm_offset = offsetof(Vertex, norm) / sizeof(float);
    constexpr int tang_offset = offsetof(Vertex, tang) / sizeof(float);
    constexpr int color_offset = offsetof(Vertex, color) / sizeof(float);
    constexpr int tex_coord_offset = offsetof(Vertex, tex_coord) / sizeof(float);
    constexpr int joints_offset = offsetof(Vertex, joints) / sizeof(float);
    constexpr int weights_offset = offsetof(Vertex, weights) / sizeof(float);
    constexpr int morph_offset = offsetof(Vertex, morph) / sizeof(float);

    const auto &st = Render::model_vertex_struct;

    std::string src;

    src += createParseFuncSource("getPos", pos_offset, GLwrap::ElementStruct::Vec3);
    src += createParseFuncSource("getNorm", norm_offset, GLwrap::ElementStruct::Vec3);
    src += createParseFuncSource("getTang", tang_offset, GLwrap::ElementStruct::Vec4);

    for (int i = 0; i < st.COLOR_COUNT; ++i){
        src += createParseFuncSource("getColor_" + std::to_string(i),
                                     color_offset + i * GLwrap::getSize(st.COLOR),
                                     st.COLOR);
    }

    for (int i = 0; i < st.TEX_COORD_COUNT; ++i){
        src += createParseFuncSource("getTexCoord_" + std::to_string(i),
                                     tex_coord_offset + i * GLwrap::getSize(st.TEX_COORD),
                                     st.TEX_COORD);
    }

    for (int i = 0; i < st.JOINTS_COUNT; ++i){
        src += createParseFuncSource("getJoints_" + std::to_string(i),
                                     joints_offset + i * GLwrap::getSize(st.JOINTS),
                                     st.JOINTS);
        src += createParseFuncSource("getWeights_" + std::to_string(i),
                                     weights_offset + i * GLwrap::getSize(st.WEIGHTS),
                                     st.WEIGHTS);
    }

    for (int i = 0; i < st.MORPH_COUNT; ++i){
        src += createParseFuncSource("getMorph_" + std::to_string(i),
                                     morph_offset + i * GLwrap::getSize(st.MORPH),
                                     st.MORPH);
    }

    return src;
}

static VShader createVShader(){
    static std::string src = "#version 420 core\n";
    src += createInputSource() + "\n";
    src += createParseFuncSourceAll() + "\n";
    src += R"(
uniform mat4 uni_model;
uniform mat4 uni_camera;

out vec4 baseColor;
out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

void main(){
    gl_Position = uni_model * vec4(getPos(), 1.0);

    baseColor = getColor_0();
    outTexCoord_0 = getTexCoord_0();
    outTexCoord_1 = getTexCoord_1();
}
    )";

    std::cout << src.c_str();

    return VShader(src);
}

static FShader createFShader(){
    static std::string src = R"(
    #version 420 core

    in vec4 baseColor;
    in vec2 outTexCoord_0;
    in vec2 outTexCoord_1;

    uniform sampler2D texture0;
    uniform sampler2D texture1;

    void main(){
        gl_FragColor = baseColor;
        // gl_FragColor = texture(texture0, outTexCoord_0) * texture(texture1, outTexCoord_1) * baseColor;
    }
    )";

    return FShader(src);
}

static Render::Renderer createRenderer(){
    return Render::Renderer(createVShader(), createFShader());
}

const Render::Renderer &Render::getRenderer(){
    static const auto renderer = createRenderer();
    return renderer;
}

static Primitive::Accessors createAccessors(){
    const int vec4_count = std::ceil((float)(sizeof(Vertex) / sizeof(float)) / 4.0);
    const int vec4_bytes = 4 * sizeof(float);

    Primitive::Accessors acc;

    for (int i = 0; i < vec4_count; ++i){
        using namespace GLwrap;
        acc[i] = new BufferAccessor(ElementStruct::Vec4,
                                    ElementType::Float,
                                    false,
                                    sizeof(Vertex),
                                    i * vec4_bytes);
    }

    return acc;
}

const Primitive::Accessors &Render::getAccessors(){
    static const auto acc = createAccessors();
    return acc;
}

Primitive *Render::createCube(){
    static const std::vector<Vertex> cube_data = {
        {.pos = {0, 0, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 0, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 1, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {0, 1, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 0, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 0, 1}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 1, 0}, .color = {{0, 1, 0, 1}}},
        {.pos = {1, 1, 1}, .color = {{0, 1, 0, 1}}},
    };

    static const std::vector<unsigned int> cube_indices = {
        0, 2, 3,
        0, 1, 3,
        0, 2, 6,
        0, 6, 4,
        0, 1, 5,
        0, 5, 4,
        7, 6, 4,
        7, 4, 5,
        7, 2, 6,
        7, 3, 2,
        7, 1, 5,
        7, 3, 1
    };

    return new Primitive(cube_data, Render::getAccessors(), &cube_indices);
}