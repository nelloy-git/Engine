#include "Graphics/Model/Model.hpp"

#include "tiny_gltf.h"

#include "Graphics/Model/TypesGltf.h"

using namespace Graphics::Model;

Model::Model(const std::string &path){

}

Model::~Model(){

}

void Model::_loadPrimitives(const tinygltf::Model &model){
    for (int i = 0; i < model.meshes.size(); ++i){
        primitives.emplace_back();
        for (int j = 0; j < model.meshes[i].primitives.size(); ++j){
            auto &gltf_prim = model.meshes[i].primitives[j];

            primitives[i].push_back(std::make_unique<Render::PrimitiveGL>());

            auto prim = primitives[i].back().get();

            prim->gl_draw_mode = gltf::toDrawMode(gltf_prim.mode);
            if (prim->gl_draw_mode == GLwrap::DrawMode::Unknown){
                throw std::runtime_error("Got GLwrap::DrawMode::Unknown");
            }


        }
    }
}

Graphics::Render::PrimitiveGL *Model::_loadPrimitive(const tinygltf::Model &model,
                                                     const tinygltf::Primitive &primitive){
    // Verify attributes size
    int attr_size = -1;
    for (auto &attr : primitive.attributes){
        auto cur_size = model.accessors[attr.second].count; 
        if (attr_size < 0){
            attr_size = cur_size;
        } else if (attr_size != cur_size){
            throw std::runtime_error("Attributes have different number of vertices."); 
        }
    }


    std::vector<Graphics::Render::VertexGL> data(attr_size);



    // auto prim = new Graphics::Render::PrimitiveGL();

    if (primitive.indices >= 0){
        std::vector<unsigned int> indices;
        auto &accessor = model.accessors[primitive.indices];
        _loadPrimitiveIndices(indices, model, accessor);

        return new Graphics::Render::PrimitiveGL(indices, data);
    } else {
        return new Graphics::Render::PrimitiveGL(data);
    }
}

void Model::_loadPrimitiveIndices(std::vector<unsigned int> &dst,
                                  const tinygltf::Model &model,
                                  const tinygltf::Accessor &accessor){
    auto &view = model.bufferViews[accessor.bufferView];
    auto &buffer = model.buffers[view.buffer];


    auto elem_type = gltf::toElemType(accessor.componentType);
    if (elem_type == GLwrap::ElementType::Unknown
        || elem_type == GLwrap::ElementType::Float
        || elem_type == GLwrap::ElementType::Double){
        
        throw std::runtime_error("Got invalid indices componentType.");
    }

    auto elem_struct = gltf::toElemStruct(accessor.type);
    if (elem_struct != GLwrap::ElementStruct::Scalar){
        throw std::runtime_error("Got invalid indices componentStruct.");
    }
    size_t elem_bytes = getSize(elem_type) * getCount(elem_struct);

    size_t step_bytes = view.byteStride == 0 ? elem_bytes : view.byteStride;

    dst.resize(accessor.count);
    for (int i = 0; i < accessor.count; ++i){
        auto addr = view.byteOffset + accessor.byteOffset + i * step_bytes;
        memcpy(&dst[i], &buffer.data.at(addr), elem_bytes);
    }
}