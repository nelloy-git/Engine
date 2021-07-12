#include "Draw/Loader/toGLwrap/IniterGLwrap.h"

// #include "Draw/gltf/gltfLoader.h"
#include "Draw/BufferCpu.h"
#include "Draw/Loader/toGLwrap/BufferGLwrap.h"
#include "Draw/Loader/toGLwrap/ModelGLwrap.h"
#include "Draw/Loader/toGLwrap/PrimitiveGLwrap.h"
#include "Draw/Loader/toGLwrap/TextureGLwrap.h"

using namespace Graphics::Draw;

IniterGLwrap::IniterGLwrap() :
    DataIniter(){
}

IniterGLwrap::~IniterGLwrap(){
}

std::shared_ptr<Model> IniterGLwrap::newModel() {
    return std::make_shared<ModelGLwrap>();
}

std::shared_ptr<Model> IniterGLwrap::newModel() const {
    return std::make_shared<ModelGLwrap>();
}

std::shared_ptr<Buffer> IniterGLwrap::newBuffer(BufferType type,
                                                BufferElemType elem_type, BufferElemStruct elem_struct,
                                                size_t count, size_t bytes, bool normalized) {
    if (type == BufferType::Other){
        return std::make_shared<BufferCpu>(elem_type, elem_struct, count, bytes, normalized);
    } else {
        return std::make_shared<BufferGLwrap>(type, elem_type, elem_struct, count, bytes, normalized);
    }
}

std::shared_ptr<Buffer> IniterGLwrap::newBuffer(BufferType type,
                                                BufferElemType elem_type, BufferElemStruct elem_struct,
                                                size_t count, size_t bytes, bool normalized) const {
    if (type == BufferType::Other){
        return std::make_shared<BufferCpu>(elem_type, elem_struct, count, bytes, normalized);
    } else {
        return std::make_shared<BufferGLwrap>(type, elem_type, elem_struct, count, bytes, normalized);
    }
}

std::shared_ptr<Primitive> IniterGLwrap::newPrimitive() {
    return std::make_shared<PrimitiveGLwrap>();
}

std::shared_ptr<Primitive> IniterGLwrap::newPrimitive() const {
    return std::make_shared<PrimitiveGLwrap>();
}

std::shared_ptr<Texture> IniterGLwrap::newTexture(int width, int height, int channels, int bpp) {
    return std::make_shared<TextureGLwrap>(width, height, channels, bpp);
}

std::shared_ptr<Texture> IniterGLwrap::newTexture(int width, int height, int channels, int bpp) const {
    return std::make_shared<TextureGLwrap>(width, height, channels, bpp);
}