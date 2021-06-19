#include "Data/Model.h"

#include "Log.h"

using namespace Graphics;

Model::Model(const std::string &path){
    tinygltf::Model *model = _loadModel(path);

    _data = std::make_shared<ModelData>(*model);
    _loadMeshes(*model);
    // model->materials[0].

    delete model;
}

Model::~Model(){

}

void Model::draw(){
    for (auto mesh : _meshes){
        mesh->draw();
    }
}

void Model::draw() const {
    for (auto mesh : _meshes){
        mesh->draw();
    }
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

void Model::_loadMeshes(const tinygltf::Model &model){
    for (int i = 0; i < model.meshes.size(); i++){
        auto &mesh = model.meshes[i];
        
        for (int j = 0; j < mesh.primitives.size(); j++){
            _meshes.push_back(std::make_shared<Mesh>(model, mesh, *_data));
        }
    }
}