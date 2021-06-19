#pragma once

#include <unordered_map>
#include <vector>

#include "GLwrap/Buffer.h"
#include "GLwrap/Tex2D.h"

#include "Data/glTF.h"
// #include "Data/Node.h"

namespace Graphics {

class ModelData {
public:
    ModelData(const tinygltf::Model &model);
    virtual ~ModelData();

    const std::vector<std::shared_ptr<GLwrap::Buffer>> &buffers();
    const std::vector<std::shared_ptr<GLwrap::Tex2D>> &textures();
    // const std::vector<std::shared_ptr<Node>> &nodes();
    
    const std::vector<std::shared_ptr<GLwrap::Buffer>> &buffers() const;
    const std::vector<std::shared_ptr<GLwrap::Tex2D>> &textures() const;
    // const std::vector<std::shared_ptr<Node>> &nodes() const;

private:
    void _initBuffers(const tinygltf::Model &model);
    void _initTextures(const tinygltf::Model &model);
    // void _initNodes(const tinygltf::Model &model);

    std::vector<std::shared_ptr<GLwrap::Buffer>> _buffers;
    std::vector<std::shared_ptr<GLwrap::Tex2D>> _textures;
    // std::vector<std::shared_ptr<Node>> _nodes;
};

}