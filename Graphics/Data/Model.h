#pragma once

#include <string>

#include "GLwrap/Vao.h"
#include "GLwrap/Vbo.h"
#include "GLwrap/Veo.h"

#include "Data/glTF.h"
#include "Data/ModelBuffer.h"

namespace Graphics {

class Model {
public:
    Model(const std::string &path);
    virtual ~Model();

private:
    std::shared_ptr<ModelBuffer> __buffer;

    std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> __vbos;
    std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> __veos;

    tinygltf::Model *__loadModel(const std::string &path);
    void __loadBuffers(const tinygltf::Model &model);
    void __loadMeshes(const tinygltf::Model &model);
};

}