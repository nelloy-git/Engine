#pragma once

#include <memory>

#include "Draw/ModelData/IFaces/Model.hpp"

namespace Graphics::Draw {

class ModelLoader {
public:
    ModelLoader() = default;
    virtual ~ModelLoader() = default;

    virtual void load(Model &dst,
                      const std::string &path,
                      std::vector<std::string> &errors) const  = 0;
};

}