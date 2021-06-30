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

    std::vector<std::shared_ptr<Scene>> scenes;
    // std::vector<>

private:
    tinygltf::Model *_loadModel(const std::string &path);

    std::shared_ptr<ModelData> _data;
};

}