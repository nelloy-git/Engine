#pragma once

#include "Graphics/Render/Base/Primitive.hpp"
#include "Graphics/Model/Model.hpp"
#include "Graphics/Model/Mesh.hpp"
#include "Graphics/Model/Node.hpp"

#include "Graphics/Model/Loader/TinyGltf/Primitive.h"
#include "Graphics/Model/Loader/TinyGltf/Types.h"
#include "Graphics/Model/Loader/TinyGltf/Utils.h"


namespace Graphics::Model::Loader {

template<Render::Base::VertexStruct S>
class TinyGltf {
public:
    TinyGltf() = delete;

    static Model<S> *newModel(const tinygltf::Model &gltf){
        auto mdl = new Model<S>();

        _loadMeshes(gltf, *mdl);
        _loadNodes(gltf, *mdl);

        return mdl;
    }

private:
    static void _loadMeshes(const tinygltf::Model &gltf_model,
                            Model<S> &mdl){
        for (int i = 0; i < gltf_model.meshes.size(); ++i){
            auto &gltf_mesh = gltf_model.meshes[i];

            mdl.meshes.emplace_back();
            for (int j = 0; j < gltf_mesh.primitives.size(); ++j){
                _addPrimitive(gltf_model, gltf_mesh.primitives[j], mdl.meshes.back());
            }
        }
    };

    static void _addPrimitive(const tinygltf::Model &gltf_model,
                              const tinygltf::Primitive &gltf_prim,
                              Mesh<S> &mesh){
        // Load primitive vertices
        auto count = _getPrimitiveVertCount(gltf_model, gltf_prim);
        std::vector<Render::Base::Vertex<S>> data(count);
        _loadAttributes(gltf_model, gltf_prim, data);

        std::cout << "Pos:" << std::endl;
        std::cout << data[0].pos[0] << ", " << data[0].pos[1] << ", " << data[0].pos[2] << std::endl;
        std::cout << data[1].pos[0] << ", " << data[1].pos[1] << ", " << data[1].pos[2] << std::endl;
        std::cout << data[2].pos[0] << ", " << data[2].pos[1] << ", " << data[2].pos[2] << std::endl;

        // auto indices = std::make_unique<std::vector<unsigned int>>();
        // std::unique_ptr<std::vector<unsigned int>> indices;
        std::unique_ptr<std::vector<unsigned int>> indices;
        if (gltf_prim.indices >= 0){
            // indices = std::make_unique<std::vector<unsigned int>>();
            // indices = new std::vector<unsigned int>();
            auto &accessor = gltf_model.accessors[gltf_prim.indices];
            indices = gltf::loadIndices(gltf_model, accessor);
            
            std::cout << "Indices: "
                      << indices->at(0) << ", "
                      << indices->at(1) << ", "
                      << indices->at(2) << std::endl;
        }
        
        mesh.primitives.emplace_back(data, indices.get());
        // return new Primitive<S>(data, Render::getAccessors(), indices.get());
    };

    static size_t _getPrimitiveVertCount(const tinygltf::Model &model,
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
        return attr_size;
    }

    static void _loadAttributes(const tinygltf::Model &gltf_model,
                                const tinygltf::Primitive &gltf_prim,
                                std::vector<Render::Base::Vertex<S>> &dst){
        for (auto &attr : gltf_prim.attributes){
            auto &name = attr.first;
            auto &gltf_accessor = gltf_model.accessors[attr.second];

            if (name == "POSITION"){
                gltf::loadPosition<S>(gltf_model, gltf_accessor, dst);
            // } else if (name == "NORMAL"){
            //     gltf::loadNormal(model, accessor, dst);
            // } else if (name == "TANGENT"){
            //     gltf::loadTangent(model, accessor, dst);
            // } else if (name == "TEXCOORD_0"){
            //     gltf::loadTex0(model, accessor, dst);
            // } else if (name == "TEXCOORD_1"){
            //     gltf::loadTex1(model, accessor, dst);
            // } else if (name == "COLOR_0"){
            //     gltf::loadColor(gltf_model, gltf_accessor, dst);
            // } else if (name == "JOINTS_0"){
            //     gltf::loadJoints(model, accessor, dst);
            // } else if (name == "WEIGHTS_0"){
            //     gltf::loadWeights(model, accessor, dst);
            }
        }
    };

    static void _loadNodes(const tinygltf::Model &gltf_model,
                           Model<S> &mdl){
        for (int i = 0; i < gltf_model.nodes.size(); ++i){
            auto &gltf_node = gltf_model.nodes[i];

            if (gltf_node.matrix.size() > 0){
                mdl.nodes.emplace_back(gltf::detailed::loadMat4x4(gltf_node.matrix));
            } else {
                auto t = gltf::detailed::loadVec3(gltf_node.translation);
                auto r = gltf::detailed::loadQuat(gltf_node.rotation);
                auto s = gltf::detailed::loadVec3(gltf_node.scale);
                mdl.nodes.emplace_back(t, r, s);
            }

            if (gltf_node.mesh >= 0){
                mdl.nodes.back().mesh = &mdl.meshes[gltf_node.mesh];
                std::cout << "Mesh detected" << std::endl;
            }
        }

        for (int i = 0; i < gltf_model.nodes.size(); ++i){
            auto &gltf_node = gltf_model.nodes[i];
            auto &node = mdl.nodes[i];
            
            for (int j = 0; j < gltf_node.children.size(); ++j){
                node.children.push_back(&mdl.nodes[gltf_node.children[j]]);
            }
        }
    };

};
 
} // namespace Graphics::Model::TinyGltf
