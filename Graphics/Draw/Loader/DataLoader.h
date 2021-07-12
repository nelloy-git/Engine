#pragma once

#include <memory>

#include "Draw/Model.h"
#include "Draw/Loader/DataIniter.h"

namespace Graphics::Draw {

class DataLoader {
public:
    DataLoader() = default;
    virtual ~DataLoader() = default;

    virtual void load(std::shared_ptr<Model> dst,
                      const std::string &path,
                      const DataIniter &initer) = 0;
    virtual void load(std::shared_ptr<Model> dst,
                      const std::string &path,
                      const DataIniter &initer) const = 0;
};

}