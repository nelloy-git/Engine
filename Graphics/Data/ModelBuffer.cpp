#include "Data/ModelBuffer.h"

#include "Log.h"

using namespace Graphics;

ModelBuffer::ModelBuffer(const tinygltf::Model &model){
    for (int i = 0; i < model.bufferViews.size(); i++){
        const tinygltf::BufferView &view = model.bufferViews[i];

        if (view.target == TINYGLTF_TARGET_ARRAY_BUFFER){
            if (__vbos.find(view.buffer) != __vbos.end()){
                continue;
            }
            auto vbo = std::make_shared<GLwrap::VBO>(view.byteLength);
            vbo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __vbos[i] = vbo;

        } else if (view.target == TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER){
            if (__veos.find(view.buffer) != __veos.end()){
                continue;
            }
            auto veo = std::make_shared<GLwrap::VEO>(view.byteLength);
            veo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __veos[i] = veo;

        } else {
            std::string err = "unknown bufferView.target,";
            LOG(ERR) << err;
            throw std::runtime_error(err);
        }
    }
}

ModelBuffer::~ModelBuffer(){

}

const std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> &ModelBuffer::vbos(){
    return __vbos;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> &ModelBuffer::veos(){
    return __veos;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::VBO>> &ModelBuffer::vbos() const{
    return __vbos;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::VEO>> &ModelBuffer::veos() const{
    return __veos;
}

