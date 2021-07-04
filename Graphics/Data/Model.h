#pragma once

#include <string>

// #include "Data/Scene.h"
// #include "Data/Node.h"
#include "Data/Material.h"
#include "Data/Mesh.h"
#include "Data/Buffer.h"

// #include "GLwrap/Buffer.h"

// #include "Data/glTF.h"
// #include "Data/Mesh.h"
// #include "Data/ModelData.h"

namespace Graphics {

class Model {
public:
    // std::vector<std::shared_ptr<Scene>> scenes;
    // std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Buffer>> buffers;

    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<GLwrap::Tex2D>> textures;
    
protected:
    Model(const std::string &path){};
    virtual ~Model(){};
};

}