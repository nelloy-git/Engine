#include "Data/Model.h"

#include "Log.h"

using namespace Graphics;

Model::Model(const std::string &path){
    tinygltf::Model *model = __loadModel(path);
    __buffer = std::make_shared<ModelBuffer>(model);
}

tinygltf::Model *Model::__loadModel(const std::string &path){
    tinygltf::TinyGLTF loader;
    tinygltf::Model *model;
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

void Model::__loadBuffers(const tinygltf::Model &model){
    for (int i = 0; i < model.bufferViews.size(); i++){
        const tinygltf::BufferView &view = model.bufferViews[i];

        if (view.target == TINYGLTF_TARGET_ARRAY_BUFFER){
            if (__vbos.find(view.buffer) != __vbos.end()){
                continue;
            }
            auto vbo = std::make_shared<GLwrap::VBO>(view.byteLength);
            vbo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __vbos[i] = vbo;

        } else if (view.target == TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER){
            if (__veos.find(view.buffer) != __veos.end()){
                continue;
            }
            auto veo = std::make_shared<GLwrap::VEO>(view.byteLength);
            veo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __veos[i] = veo;

        } else {
            std::string err = "unknown bufferView.target,";
            LOG(ERR) << err;
            throw std::runtime_error(err);
        }
    }
}

void Model::__loadMeshes(const tinygltf::Model &model){
    for (int i = 0; i < model.meshes.size(); i++){
        auto &mesh = model.meshes[i];
        
        for (int j = 0; j < mesh.primitives.size(); j++){

        }
    }
}