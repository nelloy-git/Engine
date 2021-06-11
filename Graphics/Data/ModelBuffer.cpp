#include "Data/ModelBuffer.h"

#include "Log.h"

using namespace Graphics;

ModelBuffer::ModelBuffer(const tinygltf::Model &model){
    __initDataAndIndices(model);
    __initTextures(model);
}

ModelBuffer::~ModelBuffer(){

}

const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &ModelBuffer::data(){
    return __data;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &ModelBuffer::indices(){
    return __indices;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Tex2D>> &ModelBuffer::textures(){
    return __textures;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Buffer>> &ModelBuffer::data() const{
    return __data;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Elements>> &ModelBuffer::indices() const{
    return __indices;
}

const std::unordered_map<int, std::shared_ptr<GLwrap::Tex2D>> &ModelBuffer::textures() const{
    return __textures;
}

void ModelBuffer::__initDataAndIndices(const tinygltf::Model &model){

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

void ModelBuffer::__initTextures(const tinygltf::Model &model){

    for (int i = 0; i < model.textures.size(); i++){
        auto &texture = model.textures[i];
        auto &img = model.images[texture.source];
        auto &sampler = model.samplers[texture.sampler];

        auto tex2d = std::make_shared<GLwrap::Tex2D>();
        __textures[i] = tex2d;

        std::vector<std::pair<GLwrap::Tex2DParamInt, GLuint>> sampler_params = {
            {GLwrap::Tex2DParamInt::WRAP_S, glTF::getImageWrap(sampler.wrapS)},
            {GLwrap::Tex2DParamInt::WRAP_T, glTF::getImageWrap(sampler.wrapT)},
        };

        if (sampler.minFilter > 0){
            sampler_params.push_back(
                {GLwrap::Tex2DParamInt::MIN_FILTER, glTF::getImageFilter(sampler.minFilter)}
            );
        }

        if (sampler.magFilter > 0){
            sampler_params.push_back(
                {GLwrap::Tex2DParamInt::MAG_FILTER, glTF::getImageFilter(sampler.magFilter)}
            );
        }

        tex2d->load(&img.image.at(0), img.width, img.height,
                    GLwrap::Tex2DinternalFormat::RGBA,
                    glTF::getImageFormat(img.component),
                    img.bits == 8 ? GLwrap::Tex2DpixelType::UNSIGNED_BYTE : GLwrap::Tex2DpixelType::UNSIGNED_SHORT,
                    sampler_params);
    }
}