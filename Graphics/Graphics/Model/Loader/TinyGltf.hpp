#pragma once

#include "Graphics/Render/Base/Primitive.hpp"
#include "Graphics/Model/Model.hpp"
#include "Graphics/Model/Mesh.hpp"
#include "Graphics/Model/Node.hpp"

#include "Graphics/Model/Loader/TinyGltf/Load.h"


namespace Graphics::Model::Loader {

template<Render::Base::VertexStruct S>
class TinyGltf {
public:
    TinyGltf() = delete;

    static std::unique_ptr<Model<S>> newModel(const tinygltf::Model &gltf){
        auto mdl = std::make_unique<Model<S>>();

        _loadTextures(gltf, *mdl);

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

        // Load indices if exist
        std::unique_ptr<std::vector<unsigned int>> indices;
        if (gltf_prim.indices >= 0){
            indices = std::make_unique<std::vector<unsigned int>>();
            auto &accessor = gltf_model.accessors[gltf_prim.indices];
            gltf::loadIndices(gltf_model, accessor, *indices);
        }
        
        mesh.primitives.emplace_back(data, indices.get());
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
            _loadAttribute(gltf_model, name, gltf_accessor, dst);
        }
    };

    static void _loadAttribute(const tinygltf::Model &gltf_model,
                               const std::string &name,
                               const tinygltf::Accessor &gltf_accessor,
                               std::vector<Render::Base::Vertex<S>> &dst){
        if (name == "POSITION"){
            gltf::loadPosition<S>(gltf_model, gltf_accessor, dst);
        } else if (name == "NORMAL"){
            gltf::loadNormal(gltf_model, gltf_accessor, dst);
        } else if (name == "TANGENT"){
            gltf::loadTangent(gltf_model, gltf_accessor, dst);
        } else {
            for (int i = 0; i < S.TEX_COORD_COUNT; ++i){
                if (name == "TEXCOORD_" + std::to_string(i)){
                    gltf::loadTex(gltf_model, gltf_accessor, i, dst);
                }
            }

            for (int i = 0; i < S.COLOR_COUNT; ++i){
                if (name == "COLOR_" + std::to_string(i)){
                    gltf::loadColor(gltf_model, gltf_accessor, i, dst);
                }
            }

            for (int i = 0; i < S.JOINTS_COUNT; ++i){
                if (name == "JOINTS_" + std::to_string(i)){
                    gltf::loadJoints(gltf_model, gltf_accessor, i, dst);
                }
            }

            for (int i = 0; i < S.JOINTS_COUNT; ++i){
                if (name == "WEIGHTS_" + std::to_string(i)){
                    gltf::loadJoints(gltf_model, gltf_accessor, i, dst);
                }
            }
        }
    }

    static void _loadNodes(const tinygltf::Model &gltf_model,
                           Model<S> &mdl){
        for (int i = 0; i < gltf_model.nodes.size(); ++i){
            auto &gltf_node = gltf_model.nodes[i];

            // Load matrices
            if (gltf_node.matrix.size() > 0){
                mdl.nodes.emplace_back(gltf::loadMat4x4(gltf_node.matrix));
            } else {
                auto t = gltf::loadVec3(gltf_node.translation);
                auto r = gltf::loadQuat(gltf_node.rotation);
                auto s = gltf::loadVec3(gltf_node.scale);
                mdl.nodes.emplace_back(t, r, s);
            }

            // Link mesh
            if (gltf_node.mesh >= 0){
                mdl.nodes.back().mesh = &mdl.meshes[gltf_node.mesh];
            }
        }

        // Link children
        for (int i = 0; i < gltf_model.nodes.size(); ++i){
            auto &gltf_node = gltf_model.nodes[i];
            auto &node = mdl.nodes[i];
            
            for (int j = 0; j < gltf_node.children.size(); ++j){
                node.children.push_back(&mdl.nodes[gltf_node.children[j]]);
            }
        }
    };

    static void _loadTextures(const tinygltf::Model &gltf_model,
                              Model<S> &mdl){
        for (int i = 0; i < gltf_model.textures.size(); ++i){
            auto &gltf_tex = gltf_model.textures[i];
            auto &gltf_img = gltf_model.images[gltf_tex.source];
            auto &gltf_sampler = gltf_model.samplers[gltf_tex.sampler];

            mdl.textures.emplace_back(gltf_img.width, gltf_img.height,
                                      gltf::getInternalFormat(gltf_img),
                                      gltf::getPixelFormat(gltf_img),
                                      gltf::getPixelType(gltf_img));
            mdl.textures.back().setMagFilter(gltf::getMagFilter(gltf_sampler));
            mdl.textures.back().setMinFilter(gltf::getMinFilter(gltf_sampler));
            mdl.textures.back().setWrapS(gltf::getWrapS(gltf_sampler));
            mdl.textures.back().setWrapT(gltf::getWrapT(gltf_sampler));
        }
    }

};
 
} // namespace Graphics::Model::TinyGltf
