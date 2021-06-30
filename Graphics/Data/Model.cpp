#include "Data/Model.h"

#include "Log.h"

using namespace Graphics;

Model::Model(const std::string &path){

    std::shared_ptr<tinygltf::Model> model(_loadModel(path));

    _data = std::make_shared<ModelData>(model);
    for (int i = 0; i < model->scenes.size(); i++){
        scenes.push_back(_data->getScene(i));
    }
}

Model::~Model(){

}

tinygltf::Model *Model::_loadModel(const std::string &path){
    auto model = new tinygltf::Model();
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(model, &err, &warn, path);
    if (!warn.empty()) {
        LOG(WRN) << warn;
    }

    if (!err.empty()) {
        LOG(ERR) << err;
        throw std::invalid_argument(err);
    }

    if (!res){
        err = "failed to load glTF: " + path;
        LOG(ERR) << err;
        throw std::invalid_argument(err);
    }

    return model;
}