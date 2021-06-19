#include "Data/Scene.h"

using namespace Graphics;

Scene::Scene(const tinygltf::Model &model,
             const tinygltf::Scene &scene,
             const ModelData &buffer){
    auto &list = buffer.nodes();
    for (int i = 0; i < scene.nodes.size(); i++){
        _nodes.push_back(list[i]);
    }
}

Scene::~Scene(){

}