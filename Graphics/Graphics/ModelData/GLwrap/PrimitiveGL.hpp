#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "GLwrap/Array.h"

#include "Graphics/ModelData/IFaces/Primitive.hpp"

namespace Graphics::Draw {

class PrimitiveGL : public Primitive {
public:
    PrimitiveGL();
    virtual ~PrimitiveGL();

    bool init() override;
    bool draw() const;

    std::shared_ptr<glw::Array> vao;

protected:
    bool _verifyLoc(int loc, const std::string &name);
};

}