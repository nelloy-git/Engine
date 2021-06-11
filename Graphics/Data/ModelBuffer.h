#pragma once

#include "GLwrap/Buffer.h"
#include "GLwrap/Elements.h"

#include "Data/glTF.h"

namespace Graphics {

class ModelBuffer {
public:
    ModelBuffer(const tinygltf::Model &model);
    virtual ~ModelBuffer();

    const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &data();
    const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &indices();
    
    const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &data() const;
    const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &indices() const;

private:
    std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> __data;
    std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> __indices;
};

}