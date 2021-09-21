// #include "Graphics/Model/Material.hpp"

// #include "tiny_gltf.h"

// #include "Graphics/Model/Model.hpp"

// using namespace Graphics::Model;

// Material::Material(const ModelBase &model, int index,
//                    const tinygltf::Model &gltf_model,
//                    const tinygltf::Material &material) :
//     Data(model, index){

//     // auto &gltf_pbr = material.pbrMetallicRoughness;
//     // color.tex = model->getTexture(gltf_pbr.baseColorTexture.index);
//     // color.layer = gltf_pbr.baseColorTexture.texCoord;
//     // for (int i = 0; i < 4; ++i){
//     //     color.scale[i] = gltf_pbr.baseColorFactor[i];
//     // }

//     // pbr.tex = model->getTexture(gltf_pbr.metallicRoughnessTexture.texCoord);
//     // pbr.layer = gltf_pbr.metallicRoughnessTexture.texCoord;
//     // pbr.scale[0] = gltf_pbr.metallicFactor;
//     // pbr.scale[1] = gltf_pbr.roughnessFactor;

//     // normal.tex = model->getTexture(material.normalTexture.index);
//     // normal.layer = material.normalTexture.texCoord;
//     // normal.scale[0] = material.normalTexture.scale;

//     // occlusion.tex = model->getTexture(material.occlusionTexture.index);
//     // occlusion.layer = material.occlusionTexture.texCoord;
//     // occlusion.scale[0] = material.occlusionTexture.strength;

//     // emissive.tex = model->getTexture(material.emissiveTexture.index);
//     // emissive.layer = material.emissiveTexture.texCoord;
//     // for (int i = 0; i < 3; ++i){
//     //     color.scale[i] = material.emissiveFactor[i];
//     // }
// }

// Material::~Material(){
// }