#include "Data/Model.h" 

#include "Data/AssimpImporter.h"
#include "assimp/postprocess.h"

using namespace Graphics::Data;

Model::Model(){

}

Model::~Model(){

}

bool Model::load(const std::string &path){
    auto importer = AssimpImporter::inst();

    auto scene =  std::unique_ptr<const aiScene>(importer->ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph));
    if (!scene){
        return false;
    }

    __loadMeshes(*scene);

    return true;
}

bool Model::__loadMeshes(const aiScene &scene){
    if(!scene.HasMeshes()){
        return false;
    }

    auto count = scene.mNumMeshes;
    auto ptr = scene.mMeshes;

    size_t vbo_size = 0;
    for (int i = 0; i < count; i++){
        auto mesh = std::make_shared<Mesh>(scene.mMeshes[i]);
        meshes.push_back(mesh);
    }
}