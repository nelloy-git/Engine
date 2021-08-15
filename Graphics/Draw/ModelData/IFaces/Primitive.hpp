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
    PrimitiveMorhpTarget(Buffer *pos, Buffer *norm, Buffer *tang) :
        pos(pos), norm(norm), tang(tang){};
    Buffer *pos;
    Buffer *norm;
    Buffer *tang;
};

class Primitive {
public:
    Primitive() = default;
    virtual ~Primitive() = default;

    virtual bool init() = 0;

    PrimitiveDrawMode mode;
    Buffer *indices = nullptr;
    Material *material = nullptr;
    std::map<PrimitiveAttribute, Buffer*> attributes;
    std::vector<PrimitiveMorhpTarget> morph_targets;

protected:
    bool _inited = false;

};

}