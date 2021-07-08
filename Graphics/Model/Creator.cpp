#include "Model/Creator.h"

#include "Model/gltf/gltfLoader.h"
#include "Model/Buffer/BufferCpu.h"
#include "Model/GLwrap/BufferGLwrap.h"
#include "Model/GLwrap/PrimitiveGLwrap.h"
#include "Model/GLwrap/TextureGLwrap.h"

using namespace Graphics::Model;

std::shared_ptr<Model> Creator::newModel(const std::string &path){
    static gltfLoader loader;
    return loader.load(path);
}

std::shared_ptr<Buffer> Creator::newBuffer(BufferType type,
                                           BufferElemType elem_type, BufferElemStruct elem_struct,
                                           int count, int bytes, bool normalized){
    if (type == BufferType::Other){
        return std::make_shared<BufferCpu>(elem_type, elem_struct, count, bytes, normalized);
    } else {
        return std::make_shared<BufferGLwrap>(type, elem_type, elem_struct, count, bytes, normalized);
    }
}

std::shared_ptr<Primitive> Creator::newPrimitive(){
    return std::make_shared<PrimitiveGLwrap>();
}

std::shared_ptr<Texture> Creator::newTexture(int width, int height, int channels, int bpp){
    return std::make_shared<TextureGLwrap>(width, height, channels, bpp);
}