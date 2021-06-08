#include "Data/Model.h" 

#include "Data/AssimpImporter.h"
#include "assimp/postprocess.h"

using namespace Graphics::Data;

Model::Model(){

}

Model::~Model(){

}

bool Model::load(const std::string &path){
    __path = path;

    auto importer = AssimpImporter::inst();

    auto scene =  std::unique_ptr<const aiScene>(importer->ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph));
    if (!scene){
        return false;
    }

    __loadTextures(*scene);
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
        auto mesh = std::make_shared<Mesh>(scene.mMeshes[i], __textures);
        __meshes.push_back(mesh);
    }

    return true;
}

std::string __getBasePath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

bool Model::__loadTextures(const aiScene &scene){
    if (!scene.HasMaterials()){
        return false;
    }

    auto count = scene.mNumMaterials;
    auto ptr = scene.mMaterials;
    auto root = __getBasePath(__path);

    for (int i = 0; i < count; i++){
        aiString ai_filename;
        ptr[i]->GetTexture(aiTextureType_DIFFUSE, i, &ai_filename);
        std::string filename(ai_filename.data);

        auto path = root + filename;
        __textures.push_back(std::make_shared<Texture>(path));
    }

    return true;
}