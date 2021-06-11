#pragma once

#include "GLwrap/Buffer.h"
#include "GLwrap/Elements.h"
#include "GLwrap/Tex2D.h"

#include "Data/glTF.h"

namespace Graphics {

class ModelBuffer {
public:
    ModelBuffer(const tinygltf::Model &model);
    virtual ~ModelBuffer();

    const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &data();
    const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &indices();
    const std::unordered_map<int, std::shared_ptr<GLwrap::Tex2D>> &textures();
    
    const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &data() const;
    const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &indices() const;
    const std::unordered_map<int, std::shared_ptr<GLwrap::Tex2D>> &textures() const;

private:
    void __initDataAndIndices(const tinygltf::Model &model);
    void __initTextures(const tinygltf::Model &model);

    std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> __data;
    std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> __indices;
    std::unordered_map<int, std::shared_ptr<GLwrap::Tex2D>> __textures;
};

}