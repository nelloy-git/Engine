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
    std::vector<Graphics::Render::VertexGL> data;

    // Verify attributes size
    int attr_size = -1;
    for (auto &attr : primitive.attributes){
        if (attr_size < 0){
            attr_size = model.bufferViews[attr.second].byteLength;
        }
    }


    data.resize(primitive.attributes)

    // auto prim = new Graphics::Render::PrimitiveGL();


    
    return prim;
}