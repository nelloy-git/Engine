#pragma once

#include "Graphics/Render/PrimitiveGL.hpp"

#include "Graphics/Model/Data.hpp"

namespace tinygltf {
    class Accessor;
    class Buffer;
    class BufferView;
    class Model;
    class Primitive;
}

namespace Graphics::Model {

class Primitive {
public:
    Primitive(const tinygltf::Model &model,
              const tinygltf::Primitive &primitive);

    std::unique_ptr<Render::PrimitiveGL> gl;

private:
    void _loadIndices(const tinygltf::Model &model,
                      const tinygltf::Accessor &accessor,
                      std::vector<unsigned int> &dst);

    // void _loadAttribute(const tinygltf::Model &model,
    //                     const tinygltf::Accessor &accessor,
    //                     std::vector<unsigned int> &dst);
};

}