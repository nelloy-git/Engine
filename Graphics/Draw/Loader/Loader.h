#pragma once

#include <string>

#include "Draw/Loader/DataIniter.h"
#include "Draw/Loader/DataLoader.h"

namespace Graphics::Draw {

class Loader {
public:
    enum class Input {
        gltf
    };

    enum class Output {
        GLwrap
    };

    Loader(Input in, Output out);
    virtual ~Loader();

    std::shared_ptr<Model> load(const std::string &path);

    const Input input;
    const Output output;

protected:
    std::unique_ptr<DataLoader> _getDataLoader(Input type);
    std::unique_ptr<DataIniter> _getDataIniter(Output type);

    const std::unique_ptr<DataLoader> _loader;
    const std::unique_ptr<DataIniter> _initer;

};

}