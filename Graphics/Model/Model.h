#pragma once

#include <string>

#include "Model/Buffer.h"
// #include "Model/Material.h"
// #include "Model/Mesh.h"
// #include "Model/Node.h"
// #include "Model/Scene.h"

// #include "GLwrap/Buffer.h"

// #include "Data/glTF.h"
// #include "Data/Mesh.h"
// #include "Data/ModelData.h"

namespace Graphics::Model {

class Model {
public:
    Model() = default;
    virtual ~Model() = default;

    // std::vector<std::shared_ptr<Scene>> scenes;
    // std::vector<std::shared_ptr<Node>> nodes;
    // std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Buffer>> buffers;

    // std::vector<std::shared_ptr<Material>> materials;
    // std::vector<std::shared_ptr<GLwrap::Tex2D>> textures;
    
};

}