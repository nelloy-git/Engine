#pragma once

#include "Data/glTF.h"

namespace Graphics {

class ModelBuffer {
public:
    ModelBuffer(const tinygltf::Model &model);
    virtual ~ModelBuffer();

    const std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> &vbos();
    const std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> &veos();
    
    const std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> &vbos() const;
    const std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> &veos() const;

private:
    std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> __vbos;
    std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> __veos;
};

}