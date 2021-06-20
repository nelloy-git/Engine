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

    void draw(int scene);
    void draw(int scene) const;

private:
    tinygltf::Model *_loadModel(const std::string &path);

    std::shared_ptr<ModelData> _data;
};

}