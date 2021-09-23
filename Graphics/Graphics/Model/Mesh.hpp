#pragma once

#include <memory>
#include <vector>

#include "Graphics/Render/Base/Primitive.hpp"

#include "Graphics/Model/Model.hpp"

// #include "Graphics/Model/gltf/Primitive.h"

namespace Graphics::Model {

template<Render::Base::VertexStruct S>
class Mesh {
public:
    using Primitive = Graphics::Render::Base::Primitive<S>;

    Mesh() = default;
    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = default;
    virtual ~Mesh(){};

    std::vector<Primitive> primitives;
    std::vector<float> morph;

protected:

    // Primitive *_loadPrimitive(const tinygltf::Model &model,
    //                           const tinygltf::Primitive &primitive){
    //     // Load primitive vertices
    //     auto count = _loadVerticesCount(model, primitive);
    //     std::vector<Vertex> data(count);
    //     _loadAttributes(model, primitive, data);

    //     // auto indices = std::make_unique<std::vector<unsigned int>>();
    //     std::unique_ptr<std::vector<unsigned int>> indices;
    //     if (primitive.indices >= 0){
    //         indices = std::make_unique<std::vector<unsigned int>>();
    //         auto &accessor = model.accessors[primitive.indices];
    //         gltf::loadIndices(model, accessor, *indices);
    //     }
        
    //     return new Primitive(data, indices.get());
    // };

    // size_t _loadVerticesCount(const tinygltf::Model &model,
    //                           const tinygltf::Primitive &primitive){
    //     // Verify attributes size
    //     int attr_size = -1;

    //     for (auto &attr : primitive.attributes){
    //         auto cur_size = model.accessors[attr.second].count; 
    //         if (attr_size < 0){
    //             attr_size = cur_size;
    //         } else if (attr_size != cur_size){
    //             throw std::runtime_error("Attributes have different number of vertices."); 
    //         }
    //     }

    //     return attr_size;
    // };

    // void _loadAttributes(const tinygltf::Model &model,
    //                      const tinygltf::Primitive &primitive,
    //                      std::vector<Vertex> &dst){                         
    //     for (auto &attr : primitive.attributes){
    //         auto &name = attr.first;
    //         auto &accessor = model.accessors[attr.second];

    //         if (name == "POSITION"){
    //             gltf::loadPosition(model, accessor, dst);
    //         } else if (name == "NORMAL"){
    //         //     gltf::loadNormal(model, accessor, dst);
    //         // } else if (name == "TANGENT"){
    //         //     gltf::loadTangent(model, accessor, dst);
    //         // } else if (name == "TEXCOORD_0"){
    //         //     gltf::loadTex0(model, accessor, dst);
    //         // } else if (name == "TEXCOORD_1"){
    //         //     gltf::loadTex1(model, accessor, dst);
    //         // } else if (name == "COLOR_0"){
    //         //     gltf::loadColor(model, accessor, dst);
    //         // } else if (name == "JOINTS_0"){
    //         //     gltf::loadJoints(model, accessor, dst);
    //         // } else if (name == "WEIGHTS_0"){
    //         //     gltf::loadWeights(model, accessor, dst);
    //         }
    //     }
    // };

    // Mesh(const ModelBase *model, int index,
    //      const tinygltf::Model &gltf_model, const tinygltf::Mesh &gltf_mesh) :
    //     Data(model, index){

    //     for (int i = 0; i < gltf_mesh.primitives.size(); ++i){
    //         auto gltf_prim = gltf_mesh.primitives[i];

    //         auto prim = _loadPrimitive(gltf_model, gltf_prim);
    //         primitives.emplace_back(prim);

    //         prim->gl_draw_mode = gltf::toDrawMode(gltf_prim.mode);
    //         if (prim->gl_draw_mode == GLwrap::DrawMode::Unknown){
    //             throw std::runtime_error("Got GLwrap::DrawMode::Unknown");
    //         }
    //     }
    // };

};

}