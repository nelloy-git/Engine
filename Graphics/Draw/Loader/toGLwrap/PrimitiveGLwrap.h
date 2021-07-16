#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "GLwrap/Array.h"

#include "Draw/Primitive.h"

namespace Graphics::Draw {

class PrimitiveGLwrap : public Primitive {
public:
    PrimitiveGLwrap();
    virtual ~PrimitiveGLwrap();

    bool draw() override;
    bool draw() const override;

    void init() override;

    std::shared_ptr<GLwrap::Array> vao;

protected:
    bool _inited = false;
    bool _init();

    bool _verifyLoc(int loc, const std::string &name);
};

}