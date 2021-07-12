#include "Draw/Loader/Loader.h"

#include <stdexcept>

#include "Draw/Loader/fromGltf/LoaderGltf.h"

#include "Draw/Loader/toGLwrap/IniterGLwrap.h"

using namespace Graphics::Draw;

Loader::Loader(Input in, Output out) :
    input(in),
    output(out),
    _loader(_getDataLoader(in)),
    _initer(_getDataIniter(out)){
}

Loader::~Loader(){
}

std::shared_ptr<Model> Loader::load(const std::string &path){
    auto model = _initer->newModel();
    _loader->load(model, path, *_initer);
    return model;
}

std::unique_ptr<DataIniter> Loader::_getDataIniter(Output type){
    switch(type){
        case Output::GLwrap:
            return std::make_unique<IniterGLwrap>();
        default:
            throw std::invalid_argument("Got unknown DataIniter.");
    }
}

std::unique_ptr<DataLoader> Loader::_getDataLoader(Input type){
    switch(type){
        case Input::gltf:
            return std::make_unique<LoaderGltf>();
        default:
            throw std::invalid_argument("Got unknown DataLoader");
    }
}