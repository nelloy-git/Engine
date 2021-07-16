#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "GLwrap/Array.h"

#include "Draw/ModelData/Primitive.h"

namespace Graphics::Draw {

class PrimitiveGL : public Primitive {
public:
    PrimitiveGL();
    virtual ~PrimitiveGL();

    bool draw() const override;
    void init() override;

    std::shared_ptr<GLwrap::Array> vao;

protected:
    bool _inited = false;
    bool _verifyLoc(int loc, const std::string &name);
};

}