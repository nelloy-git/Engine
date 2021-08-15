#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "GLwrap/Array.h"

#include "Draw/ModelData/IFaces/Primitive.hpp"

namespace Graphics::Draw {

class PrimitiveGL : public Primitive {
public:
    PrimitiveGL();
    virtual ~PrimitiveGL();

    bool init() override;
    bool draw() const;

    std::shared_ptr<GLwrap::BufferArray> vao;

protected:
    bool _verifyLoc(int loc, const std::string &name);
};

}