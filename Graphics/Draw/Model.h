#pragma once

#include <string>

#include "Draw/Buffer.h"
#include "Draw/Mesh.h"
#include "Draw/Material.h"
#include "Draw/Texture.h"
// #include "Draw/Mesh.h"
// #include "Draw/Node.h"
// #include "Draw/Scene.h"

// #include "GLwrap/Buffer.h"

// #include "Data/glTF.h"
// #include "Data/Mesh.h"
// #include "Data/ModelData.h"

namespace Graphics::Draw {

class Model {
public:
    Model();
    virtual ~Model() = 0;

    // std::vector<std::shared_ptr<Scene>> scenes;
    // std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Buffer>> buffers;
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Texture>> textures;

    // std::vector<std::shared_ptr<Material>> materials;
    
};

}