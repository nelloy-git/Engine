#pragma once

#include <optional>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Draw/ModelData/IFaces/Buffer.hpp"
#include "Draw/ModelData/IFaces/Material.hpp"

namespace Graphics::Draw {

struct PrimitiveMorhpTarget {
    std::shared_ptr<Buffer> pos;
    std::shared_ptr<Buffer> norm;
    std::shared_ptr<Buffer> tang;
};

class Primitive {
public:
    Primitive() = default;
    virtual ~Primitive() = default;

    virtual bool init() = 0;

    PrimitiveDrawMode mode;
    std::shared_ptr<Buffer> indices = nullptr;
    std::shared_ptr<Material> material = nullptr;
    std::map<PrimitiveAttribute, std::shared_ptr<Buffer>> attributes;
    std::vector<PrimitiveMorhpTarget> morph_targets;

protected:
    bool _inited = false;

};

}