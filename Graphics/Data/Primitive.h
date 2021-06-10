#pragma once

#include <unordered_map>

#include "GLwrap/BufferAttribute.h"
#include "GLwrap/Vao.h"
#include "GLwrap/Vbo.h"
#include "GLwrap/Veo.h"

#include "Data/glTF.h"
#include "Data/ModelBuffer.h"

namespace Graphics {

class Primitive {
public:
    Primitive(const tinygltf::Model &model,
              const tinygltf::Primitive &primitive,
              const ModelBuffer &buffer);

private:
    std::unordered_map<std::string, std::shared_ptr<GLwrap::BufferAttrubute>> __attributes;
    std::shared_ptr<GLwrap::VEO> __veo;
    std::shared_ptr<GLwrap::VAO> __vao;
};

}