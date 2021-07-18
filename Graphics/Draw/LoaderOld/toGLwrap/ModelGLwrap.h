#pragma once

#include "Draw/Model.h"

namespace Graphics::Draw {

class ModelGLwrap : public Model {
public:
    ModelGLwrap();
    virtual ~ModelGLwrap() override;
};

}