#include "Data/Scene.h"

#include "Data/ModelData.h"

using namespace Graphics;

Scene::Scene(const tinygltf::Model &model,
             const tinygltf::Scene &scene,
             ModelData &data){

    for (int i = 0; i < scene.nodes.size(); i++){
        auto node_pos = scene.nodes[i];
        auto iter = data.nodes.find(node_pos);
        if (iter == data.nodes.end()){
            data.nodes[node_pos] = std::make_shared<Node>(model, model.nodes[node_pos], data);
            iter = data.nodes.find(node_pos);
        }
        nodes.push_back(iter->second);
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