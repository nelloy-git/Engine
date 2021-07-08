#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "GLwrap/Array.h"

#include "Model/Primitive.h"

namespace Graphics::Model {

class PrimitiveGLwrap : public Primitive {
public:
    PrimitiveGLwrap();
    virtual ~PrimitiveGLwrap();

    bool draw() override;
    bool draw() const override;

    void update() override;

    std::shared_ptr<GLwrap::Array> vao;

protected:
    bool _inited = false;
    bool _init();

    bool _verifyLoc(int loc, const std::string &name);
};

}