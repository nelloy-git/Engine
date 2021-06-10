#include "Data/Primitive.h"

using namespace Graphics;

Primitive::Primitive(const tinygltf::Model &model,
                     const tinygltf::Primitive &primitive,
                     const ModelBuffer &buffer){

    auto &accessor = model.accessors[primitive.indices];
    auto &view = model.bufferViews[accessor.bufferView];
    auto veo = buffer.veos().at(view.buffer);

    // for ()    
}