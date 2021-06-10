#include "Data/Model_glTF.h" 

#include <iostream>

#include "Utils/Log.h"

using namespace Graphics::Data;

Model_glTF::Model_glTF(){
}

Model_glTF::~Model_glTF(){

}

void Model_glTF::draw(){
    for (auto mesh : __meshes){
        mesh->draw();
    }
}

bool Model_glTF::load(const std::string &path){

    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    __meshes.clear();

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, path);
    if (!warn.empty()) {
        LOG(WRN) << warn;
        return true;
    }

    if (!err.empty()) {
        LOG(ERR) << err;
        return false;
    }

    if (!res){
        LOG(WRN) << "failed to load glTF: " << path;
        return false;
    }

    const tinygltf::Scene &scene = model.scenes[model.defaultScene];

    for (auto pos : scene.nodes){
        __loadNode(model, model.nodes[pos]);
    }    

    return true;
}

void Model_glTF::__loadNode(const tinygltf::Model &model,
                            const tinygltf::Node &node){

    __meshes.push_back(std::make_shared<Mesh_glTF>(model, model.meshes[node.mesh]));

    for (auto pos : node.children){
        __loadNode(model, model.nodes[pos]);
    }
}