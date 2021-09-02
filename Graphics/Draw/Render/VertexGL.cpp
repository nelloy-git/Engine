#include "Draw/Render/VertexGL.hpp"

using namespace Graphics::Render;

const AccessorsGL *VertexGL::getAccessors(){
    constexpr auto step = sizeof(VertexGL);
    constexpr auto size = 4 * sizeof(float);

    using namespace GLwrap;

    static const AccessorsGL list = ([](){
        AccessorsGL list;
        for (unsigned int i = 0; i < 15; ++i){
            list[i] = new BufferAccessor(ElementStruct::Vec4, ElementType::Float, false, step, i * size);
        }
        return list;
    })();

    return &list;
}