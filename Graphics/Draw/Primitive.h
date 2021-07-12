#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "Draw/Buffer.h"
#include "Draw/Material.h"

namespace Graphics::Draw {

struct PrimitiveTarget {
    std::shared_ptr<Buffer> pos;
    std::shared_ptr<Buffer> norm;
    std::shared_ptr<Buffer> tang;
};

class Primitive {
public:

    virtual bool draw() = 0;
    virtual bool draw() const = 0;

    virtual void update() = 0;

    PrimitiveDrawMode mode;
    std::shared_ptr<Buffer> indices;
    std::shared_ptr<Material> material;
    std::map<PrimitiveAttribute, std::shared_ptr<Buffer>> attributes;
    std::vector<PrimitiveTarget> targets;

protected:
    Primitive(){};
    virtual ~Primitive(){};

};

}