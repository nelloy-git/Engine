#pragma once

#include <vector>

#include "Graphics/Render/Base/Vertex.hpp"

#include "Graphics/Model/Loader/TinyGltf/Utils.h"

namespace Graphics::Model::gltf {

void loadIndices(const tinygltf::Model &model,
                 const tinygltf::Accessor &accessor,
                 std::vector<unsigned int> &dst){
    auto elem_type = gltf::getElemType(accessor);
    auto elem_struct = gltf::getElemStruct(accessor);

    if (elem_struct != glw::DataSize::Scalar){
        detailed::throwErr("Got invalid indices componentStruct.");
    }

    dst.resize(accessor.count);
    auto dst_ptr = reinterpret_cast<char *>(dst.data());
    auto dst_step = sizeof(unsigned int);

    switch (elem_type){
    case glw::gpu_data_type::GLubyte:
        detailed::loadAccessor<unsigned int, 1, unsigned char, 1>
            (model, accessor, dst_ptr, 0, dst_step);
        break;
        
    case glw::gpu_data_type::GLushort:
        detailed::loadAccessor<unsigned int, 1, unsigned short int, 1>
            (model, accessor, dst_ptr, 0, dst_step);
        break;
        
    case glw::gpu_data_type::GLuint:
        detailed::loadAccessor<unsigned int, 1, unsigned int, 1>
            (model, accessor, dst_ptr, 0, dst_step);
        break;
    
    default:
        detailed::throwErr("Got invalid indices componentType.");
    }
}

using VertexStruct = Render::Base::VertexStruct;
template<VertexStruct S>
using Vertex = Render::Base::Vertex<S>;

template<VertexStruct S>
inline void loadPosition(const tinygltf::Model &model,
                         const tinygltf::Accessor &accessor,
                         std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(3, glw::getSize(S.POS))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, pos), sizeof(Vertex<S>));
};

template<VertexStruct S>
void loadNormal(const tinygltf::Model &model,
                const tinygltf::Accessor &accessor,
                std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(3, glw::getSize(S.NORM))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, norm), sizeof(Vertex<S>));
};

template<VertexStruct S>
void loadTangent(const tinygltf::Model &model,
                 const tinygltf::Accessor &accessor,
                 std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(4, glw::getSize(S.TANG))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, tang), sizeof(Vertex<S>));
};

template<VertexStruct S>
void loadTex(const tinygltf::Model &model,
             const tinygltf::Accessor &accessor,
             size_t n,
             std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(2, glw::getSize(S.TEX_COORD))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, tex_coord) + n * sizeof(Vertex<S>::tex_coord[0]), sizeof(Vertex<S>));
};

template<VertexStruct S>
void loadColor(const tinygltf::Model &model,
               const tinygltf::Accessor &accessor,
               size_t n,
               std::vector<Vertex<S>> &dst){
    if (gltf::getElemStruct(accessor) == glw::DataSize::Vec3){
        detailed::loadVecNormalized<detailed::min<size_t>(3, glw::getSize(S.COLOR))>
            (model, accessor, reinterpret_cast<char *>(dst.data()),
             offsetof(Vertex<S>, color) + n * sizeof(Vertex<S>::color[0]), sizeof(Vertex<S>));
        
        for (int i = 0; i < dst.size(); ++i){
            dst[i].color[n][3] = 1;
        }
    } else {
        detailed::loadVecNormalized<detailed::min<size_t>(4, glw::getSize(S.COLOR))>
            (model, accessor, reinterpret_cast<char *>(dst.data()),
             offsetof(Vertex<S>, color) + n * sizeof(Vertex<S>::color[0]), sizeof(Vertex<S>));
    }
};

template<VertexStruct S>
void loadJoints(const tinygltf::Model &model,
                const tinygltf::Accessor &accessor,
                size_t n,
                std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(4, glw::getSize(S.JOINTS))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, joints) + n * sizeof(Vertex<S>::joints[0]), sizeof(Vertex<S>));
};

template<VertexStruct S>       
void loadWeights(const tinygltf::Model &model,
                 const tinygltf::Accessor &accessor,
                 size_t n,
                 std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(4, glw::getSize(S.JOINTS))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, weights) + n * sizeof(Vertex<S>::weights[0]), sizeof(Vertex<S>));
};

template<VertexStruct S>       
void loadMorph(const tinygltf::Model &model,
               const tinygltf::Accessor &accessor,
               size_t n,
               std::vector<Vertex<S>> &dst){
    detailed::loadVecNormalized<detailed::min<size_t>(4, glw::getSize(S.MORPH))>
        (model, accessor, reinterpret_cast<char *>(dst.data()),
         offsetof(Vertex<S>, morph) + n * sizeof(Vertex<S>::morph[0]), sizeof(Vertex<S>));
}

glm::mat4 loadMat4x4(const std::vector<double> &src){
    glm::mat4 mat;
    for (int i = 0; i < 16; ++i){
        int x = i / 4;
        int y = i % 4;
        mat[x][y] = src[i];
    }
    return mat;
}

glm::vec3 loadVec3(const std::vector<double> &src){
    glm::vec3 vec;
    for (int i = 0; i < src.size(); ++i){
        vec[i] = src[i];
    }
    return vec;
}

glm::quat loadQuat(const std::vector<double> &src){
    glm::quat quat;
    for (int i = 0; i < src.size(); ++i){
        quat[i] = src[i];
    }
    return quat;
}

}