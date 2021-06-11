#include "Data/Model.h"

#include "Log.h"

using namespace Graphics;

Model::Model(const std::string &path){
    tinygltf::Model *model = __loadModel(path);

    __buffer = std::make_shared<ModelBuffer>(*model);
    __loadMeshes(*model);

    delete model;
}

Model::~Model(){

}

void Model::draw(){
    for (auto mesh : __meshes){
        mesh->draw();
    }
}

tinygltf::Model *Model::__loadModel(const std::string &path){
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

void Model::__loadMeshes(const tinygltf::Model &model){
    for (int i = 0; i < model.meshes.size(); i++){
        auto &mesh = model.meshes[i];
        
        for (int j = 0; j < mesh.primitives.size(); j++){
            __meshes.push_back(std::make_shared<Mesh>(model, mesh, *__buffer));
        }
    }
}