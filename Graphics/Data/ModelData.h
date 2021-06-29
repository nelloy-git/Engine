#pragma once

#include <map>
#include <vector>

#include "GLwrap/Buffer.h"
#include "GLwrap/Tex2D.h"

#include "Data/glTF.h"
#include "Data/Mesh.h"
#include "Data/Node.h"
#include "Data/Scene.h"

namespace Graphics {

class ModelData {
public:
    ModelData(const tinygltf::Model &model);
    virtual ~ModelData();

    std::map<int, std::shared_ptr<Scene>> scenes;
    std::map<int, std::shared_ptr<Node>> nodes;
    std::map<int, std::shared_ptr<Mesh>> meshes;
    // std::map<int, std::shar

    std::unordered_map<int, char*> buffers;


    // const std::vector<std::shared_ptr<GLwrap::Buffer>> &buffers();
//     const std::vector<std::shared_ptr<GLwrap::Tex2D>> &textures();
//     const std::vector<std::shared_ptr<Mesh>> &meshes();
//     const std::vector<std::shared_ptr<Node>> &nodes();
//     const std::vector<std::shared_ptr<Scene>> &scenes();
    
//     const std::vector<std::shared_ptr<GLwrap::Buffer>> &buffers() const;
//     const std::vector<std::shared_ptr<GLwrap::Tex2D>> &textures() const;
//     const std::vector<std::shared_ptr<Mesh>> &meshes() const;
//     const std::vector<std::shared_ptr<Node>> &nodes() const;
//     const std::vector<std::shared_ptr<Scene>> &scenes() const;

// private:
//     void _initBuffers(const tinygltf::Model &model);
//     void _initTextures(const tinygltf::Model &model);
//     void _initMeshes(const tinygltf::Model &model);
//     void _initNodes(const tinygltf::Model &model);
//     void _initScenes(const tinygltf::Model &model);

//     std::vector<std::shared_ptr<GLwrap::Buffer>> _buffers;
//     std::vector<std::shared_ptr<GLwrap::Tex2D>> _textures;
//     std::vector<std::shared_ptr<Mesh>> _meshes;
//     std::vector<std::shared_ptr<Node>> _nodes;
//     std::vector<std::shared_ptr<Scene>> _scenes;
};

}

// 5труба+8текстиль+16трактор+8.5песок+17щебень+3работник