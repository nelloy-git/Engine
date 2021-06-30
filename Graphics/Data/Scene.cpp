#include "Data/Scene.h"

#include "Data/ModelData.h"

using namespace Graphics;

Scene::Scene(const tinygltf::Scene &scene,
             ModelData &data){

    for (int i = 0; i < scene.nodes.size(); i++){
        nodes.push_back(data.getNode(scene.nodes[i]));
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