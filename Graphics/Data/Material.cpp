#include "Data/Material.h"

#include "GLwrap/Program.h"

#include "Data/ModelData.h"

using namespace Graphics; 

Material::Material(const tinygltf::Model &model,
                   const tinygltf::Material &material,
                   const ModelData &buffer){

    auto &pbr = material.pbrMetallicRoughness;
    for (int i = 0; i < 4; i++){
        __base_color.push_back(pbr.baseColorFactor[i]);
    }

    __base_texture = buffer.textures().at(pbr.baseColorTexture.index);
    __base_texture_uv = pbr.baseColorTexture.texCoord;
}

Material::~Material(){

}

void Material::apply(){
    auto progr = GLwrap::Program::getActive();
    if (progr == nullptr){
        return;
    }

    progr->setUniformVec4f("baseColor", &__base_color.at(0));
    __base_texture->setActive(__base_texture_uv);
}