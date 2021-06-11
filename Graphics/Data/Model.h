#pragma once

#include <string>

#include "GLwrap/Buffer.h"

#include "Data/glTF.h"
#include "Data/Mesh.h"
#include "Data/ModelBuffer.h"

namespace Graphics {

class Model {
public:
    Model(const std::string &path);
    virtual ~Model();

    void draw();

private:
    std::shared_ptr<ModelBuffer> __buffer = nullptr;
    std::vector<std::shared_ptr<Mesh>> __meshes;

    tinygltf::Model *__loadModel(const std::string &path);
    void __loadMeshes(const tinygltf::Model &model);
};

}