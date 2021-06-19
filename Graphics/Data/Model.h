#pragma once

#include <string>

#include "GLwrap/Buffer.h"

#include "Data/glTF.h"
#include "Data/Mesh.h"
#include "Data/ModelData.h"

namespace Graphics {

class Model {
public:
    Model(const std::string &path);
    virtual ~Model();

    void draw();
    void draw() const;

private:
    tinygltf::Model *_loadModel(const std::string &path);
    void _loadMeshes(const tinygltf::Model &model);

    std::shared_ptr<ModelData> _data;
    std::vector<std::shared_ptr<Mesh>> _meshes;
};

}