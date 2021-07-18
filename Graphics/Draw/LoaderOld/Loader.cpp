#include "Draw/Loader/Loader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Draw/Loader/fromGltf/LoaderGltf.h"
#include "Draw/Loader/toGLwrap/IniterGLwrap.h"
#include "Log.h"

using namespace Graphics::Draw;

Loader::Loader(Input in, Output out) :
    input(in),
    output(out),
    _loader(_getDataLoader(in)),
    _initer(_getDataIniter(out)){
}

Loader::~Loader(){
}

std::shared_ptr<Model> Loader::loadModel(const std::string &path){
    auto model = _initer->newModel();
    _loader->load(model, path, *_initer);
    return model;
}

std::shared_ptr<Shader> Loader::loadShader(const std::vector<std::string> &paths){
    std::vector<std::string> sources;

    for (int i = 0; i < paths.size(); ++i){
        sources.push_back(_readTextFile(paths[i]));
    }

    auto shader = _initer->newShader(sources);
    if (shader->verify()){
        return shader;
    } else {
        return nullptr;
    }
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

std::string Loader::_readTextFile(const std::string &path){
    std::string code;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(path);
        std::stringstream str_stream;

        std::string line;
        while(!file.eof()){
	        std::getline(file, line); // Saves the line in STRING.
	        code += line + "\n"; 
        }
        file.close();
    } catch(std::ifstream::failure e){
        LOG(WRN) << "can not read file";
    }

    return code;
}