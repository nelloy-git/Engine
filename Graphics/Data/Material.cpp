#include "Data/Material.h"

#include <stdexcept>

#include "GLwrap/Program.h"

#include "Data/ModelData.h"

using namespace Graphics; 

Material::Material(const tinygltf::Model &model,
                   const tinygltf::Material &material,
                   ModelData &data){

    auto &pbr = material.pbrMetallicRoughness;
    for (int i = 0; i < 4; i++){
        _base_color.push_back(pbr.baseColorFactor[i]);
    }

    // auto tex_pos = pbr.baseColorTexture.index;
    // auto tex_iter = data.textures.find(tex_pos);
    // if (tex_iter == data.textures.end()){
    //     throw std::runtime_error("Can not get texture");
    // }

    // _base_texture = tex_iter->second;
    // _base_texture_uv = pbr.baseColorTexture.texCoord;
}

Material::~Material(){

}

void Material::apply(){
    auto progr = GLwrap::Program::getActive();
    if (progr == nullptr){
        return;
    }

    progr->setUniformVec4f("baseColor", &_base_color.at(0));
    _base_texture->setActive(_base_texture_uv);
}