#include "Data/ModelBuffer.h"

#include "Log.h"

using namespace Graphics;

ModelBuffer::ModelBuffer(const tinygltf::Model &model){
    // LOG(MSG) << model.bufferViews.size();
    for (int i = 0; i < model.bufferViews.size(); i++){
        const tinygltf::BufferView &view = model.bufferViews[i];

        if (view.target == TINYGLTF_TARGET_ARRAY_BUFFER){
            if (__data.find(view.buffer) != __data.end()){
                continue;
            }
            auto vbo = std::make_shared<GLwrap::Buffer>(GLwrap::BufferType::ARRAY, view.byteLength);
            vbo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __data[i] = vbo;

        } else if (view.target == TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER){
            if (__indices.find(view.buffer) != __indices.end()){
                continue;
            }
            auto veo = std::make_shared<GLwrap::Elements>(view.byteLength);
            veo->load(&model.buffers[view.buffer].data.at(view.byteOffset));
            __indices[i] = veo;

        } else {
            std::string err = "unknown bufferView.target,";
            LOG(ERR) << err;
            throw std::runtime_error(err);
        }
    }
}

ModelBuffer::~ModelBuffer(){

}

const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &ModelBuffer::data() const{
    return __data;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &ModelBuffer::indices() const{
    return __indices;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &ModelBuffer::data(){
    return __data;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &ModelBuffer::indices(){
    return __indices;
}

