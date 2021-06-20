#include "Data/Scene.h"

#include "Data/ModelData.h"

using namespace Graphics;

Scene::Scene(const tinygltf::Model &model,
             const tinygltf::Scene &scene,
             const ModelData &data){

    auto &list = data.nodes();
    for (int i = 0; i < scene.nodes.size(); i++){
        nodes.push_back(list[scene.nodes[i]]);
    }
}

Scene::~Scene(){

}

void Scene::draw(){
    for (auto &node : nodes){
        node->draw();
    }
}

void Scene::draw() const {
    for (auto &node : nodes){
        node->draw();
    }
}