#include "Draw/Render/GLwrap/Default/ShaderVertexGLDefault.hpp"

using namespace Graphics::Render;
using namespace GLwrap;

ShaderVertexGLDefault::ShaderVertexGLDefault() :
    ShaderVertexGL<ShaderInputGL>(_getSources()){
}

ShaderVertexGLDefault::~ShaderVertexGLDefault(){
}

PrimitiveGL<ShaderInputGL> *
ShaderVertexGLDefault::createPrimitive(const std::vector<unsigned int> &indices,
                                       const std::vector<Input> &data){

    BufferTyped<Input> gl_data(BufferType::Array, data);
    auto &gl_accessors = getAccessors();
    BufferTyped<unsigned int> gl_indices(BufferType::IndexArray, indices);

    return new PrimitiveGL(gl_data, gl_accessors, gl_indices);
}

const std::string &ShaderVertexGLDefault::_getSources(){
    static std::string src = 
        #include "Draw/Render/GLwrap/Default/default.vert.glsl"
    ;
    return src;
}

const std::unordered_map<BufferArray::Layout, const BufferAccessor *> &
ShaderVertexGLDefault::getAccessors(){
    constexpr auto step = sizeof(ShaderVertexGL);
    constexpr auto size = 4 * sizeof(float);
    
    static const std::unordered_map<BufferArray::Layout, const BufferAccessor *> list {
        {0,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 0  * size)},
        {1,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 4  * size)},
        {2,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 8  * size)},
        {3,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 12 * size)},
        {4,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 16 * size)},
        {5,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 20 * size)},
        {6,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 24 * size)},
        {7,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 28 * size)},
        {8,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 32 * size)},
        {9,  new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 36 * size)},
        {10, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 40 * size)},
        {11, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 44 * size)},
        {12, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 48 * size)},
        {13, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 52 * size)},
        {14, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 56 * size)},
        {15, new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, 60 * size)},
    };
    return list;
}