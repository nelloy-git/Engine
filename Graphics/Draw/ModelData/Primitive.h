#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "Draw/ModelData/Buffer.h"
#include "Draw/Material.h"

namespace Graphics::Draw {

struct PrimitiveMorhpTarget {
    std::shared_ptr<Buffer> pos;
    std::shared_ptr<Buffer> norm;
    std::shared_ptr<Buffer> tang;
};

class Primitive {
public:
    virtual bool draw() const = 0;
    virtual void init() = 0;

    PrimitiveDrawMode mode;
    std::shared_ptr<Buffer> indices = nullptr;
    std::shared_ptr<Material> material = nullptr;
    std::map<PrimitiveAttribute, std::shared_ptr<Buffer>> attributes;
    std::vector<PrimitiveMorhpTarget> morph_targets;

protected:
    Primitive(){};
    virtual ~Primitive(){};

};

}