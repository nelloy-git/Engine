#include "Data/ModelData.h"

#include "Log.h"

using namespace Graphics;

ModelData::ModelData(std::shared_ptr<tinygltf::Model> model) :
    _model(model){
    // _initBuffers(model);
    // _initTextures(model);
    // _initMeshes(model);
    // _initNodes(model);
    // _initScenes(model);
}

ModelData::~ModelData(){

}

std::shared_ptr<Scene> ModelData::getScene(int pos){
    return _getData(pos, _scenes, _model->scenes[pos]);
}

std::shared_ptr<Node> ModelData::getNode(int pos){
    return _getData(pos, _nodes, _model->nodes[pos]);
}

std::shared_ptr<Mesh> ModelData::getMesh(int pos){
    return _getData(pos, _meshes, _model->meshes[pos]);
}

std::shared_ptr<BufferView> ModelData::getBufferView(int pos){
    auto &tiny_view = _model->bufferViews[pos];
    auto view = _getData(pos, _buffers, tiny_view);
    view->buffer->write(&_model->buffers[tiny_view.buffer].data.at(tiny_view.byteOffset));
    return view;
}

std::shared_ptr<Accessor> ModelData::getAccessor(int pos){
    return _getData(pos, _accessors, _model->accessors[pos]);
}

// const std::vector<std::shared_ptr<GLwrap::Buffer>> &ModelData::buffers(){
//     return _buffers;
// }

// const std::vector<std::shared_ptr<GLwrap::Tex2D>> &ModelData::textures(){
//     return _textures;
// }

// const std::vector<std::shared_ptr<Mesh>> &ModelData::meshes(){
//     return _meshes;
// }

// const std::vector<std::shared_ptr<Node>> &ModelData::nodes(){
//     return _nodes;
// }

// const std::vector<std::shared_ptr<Scene>> &ModelData::scenes(){
//     return _scenes;
// }

// const std::vector<std::shared_ptr<GLwrap::Buffer>> &ModelData::buffers() const{
//     return _buffers;
// }

// const std::vector<std::shared_ptr<GLwrap::Tex2D>> &ModelData::textures() const{
//     return _textures;
// }

// const std::vector<std::shared_ptr<Mesh>> &ModelData::meshes() const{
//     return _meshes;
// }

// const std::vector<std::shared_ptr<Node>> &ModelData::nodes() const{
//     return _nodes;
// }

// const std::vector<std::shared_ptr<Scene>> &ModelData::scenes() const{
//     return _scenes;
// }

// void ModelData::_initBuffers(const tinygltf::Model &model){
//     const static auto VERTEX_ARRAY = GLwrap::BufferType::ARRAY;
//     const static auto INDEX_ARRAY = GLwrap::BufferType::ELEMENT_ARRAY;

//     for (auto &view : model.bufferViews){
//         bool is_vertex = view.target == TINYGLTF_TARGET_ARRAY_BUFFER;
//         auto gl_buffer = std::make_shared<GLwrap::Buffer>(
//             is_vertex ? VERTEX_ARRAY : INDEX_ARRAY, view.byteLength);
//         gl_buffer->load(&model.buffers[view.buffer].data.at(view.byteOffset));
//         _buffers.push_back(gl_buffer);
//     }
// }

// void ModelData::_initTextures(const tinygltf::Model &model){

//     for (int i = 0; i < model.textures.size(); i++){
//         auto &texture = model.textures[i];
//         auto &img = model.images[texture.source];
//         auto &sampler = model.samplers[texture.sampler];

//         auto tex2d = std::make_shared<GLwrap::Tex2D>();
//         _textures.push_back(tex2d);

//         std::vector<std::pair<GLwrap::Tex2DParamInt, GLuint>> sampler_params = {
//             {GLwrap::Tex2DParamInt::WRAP_S, glTF::getImageWrap(sampler.wrapS)},
//             {GLwrap::Tex2DParamInt::WRAP_T, glTF::getImageWrap(sampler.wrapT)},
//         };

//         if (sampler.minFilter > 0){
//             sampler_params.push_back(
//                 {GLwrap::Tex2DParamInt::MIN_FILTER, glTF::getImageFilter(sampler.minFilter)}
//             );
//         }

//         if (sampler.magFilter > 0){
//             sampler_params.push_back(
//                 {GLwrap::Tex2DParamInt::MAG_FILTER, glTF::getImageFilter(sampler.magFilter)}
//             );
//         }

//         tex2d->load(&img.image.at(0), img.width, img.height,
//                     GLwrap::Tex2DinternalFormat::RGBA,
//                     glTF::getImageFormat(img.component),
//                     img.bits == 8 ? GLwrap::Tex2DpixelType::UNSIGNED_BYTE : GLwrap::Tex2DpixelType::UNSIGNED_SHORT,
//                     sampler_params);
//     }
// }

// void ModelData::_initMeshes(const tinygltf::Model &model){
//     for (int i = 0; i < model.meshes.size(); i++){
//         _meshes.push_back(std::make_shared<Mesh>(model, model.meshes[i], *this));
//     }   
// }

// void ModelData::_initNodes(const tinygltf::Model &model){
//     for (int i = 0; i < model.nodes.size(); i++){
//         _nodes.push_back(std::make_shared<Node>(model, model.nodes[i], *this));
//     }

//     for (int i = 0; i < model.nodes.size(); i++){
//         for (int j = 0; j < model.nodes[i].children.size(); j++){
//             _nodes[i]->children.push_back(_nodes[model.nodes[i].children[j]]);
//         }
//     }
// }

// void ModelData::_initScenes(const tinygltf::Model &model){
//     for (int i = 0; i < model.scenes.size(); i++){
//         _scenes.push_back(std::make_shared<Scene>(model, model.scenes[i], *this));
//     }
// }