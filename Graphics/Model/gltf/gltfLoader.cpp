#include "Model/gltf/gltfLoader.h"

#include "Model/Buffer/BufferCpu.h"
#include "Model/Buffer/BufferGL.h"

#include "Log.h"

using namespace Graphics::Model;

std::shared_ptr<Model> gltfLoader::load(const std::string &path){
    auto data = _loadGltfModel(path);
    auto res = std::make_shared<Model>();

    for (auto &accessor : data->accessors){
        res->buffers.push_back(_loadBuffer(accessor, *data));
    }

    return res;
}

tinygltf::Model *gltfLoader::_loadGltfModel(const std::string &path){
    auto model = new tinygltf::Model();
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(model, &err, &warn, path);
    if (!warn.empty()) {
        LOG(WRN) << warn;
    }

    if (!err.empty()) {
        LOG(ERR) << err;
        return nullptr;
    }

    if (!res){
        LOG(ERR) << "failed to load glTF: " << path;
        return nullptr;
    }

    return model;
}

std::shared_ptr<Buffer> gltfLoader::_loadBuffer(const tinygltf::Accessor &accessor,
                                                const tinygltf::Model &model){

    auto &view = model.bufferViews[accessor.bufferView];
    auto &data = model.buffers[view.buffer];

    ComponentType data_type = gltfConvert::getComponentType(accessor.componentType);
    ComponentSize data_size = gltfConvert::getComponentSize(accessor.type);
    size_t elem_size = static_cast<int>(data_size) * gltfConvert::getComponentTypeSize(data_type);
    size_t stride = view.byteStride == 0 ? elem_size : view.byteStride;

    std::shared_ptr<Buffer> buffer;
    if (view.target == TINYGLTF_TARGET_ARRAY_BUFFER){
        buffer = std::make_shared<BufferGL>(BufferType::Vertex, data_type, data_size,
                                            accessor.count, accessor.count * elem_size,
                                            accessor.normalized);

    } else if (view.target == TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER){
        buffer = std::make_shared<BufferGL>(BufferType::Index, data_type, data_size,
                                            accessor.count, accessor.count * elem_size,
                                            accessor.normalized);

    } else {
        buffer = std::make_shared<BufferCpu>(data_type, data_size,
                                             accessor.normalized, accessor.count,
                                             accessor.count * elem_size);
    }

    for (auto i = 0; i < accessor.count; i++){
        if (!buffer->write(&data.data.at(view.byteOffset + accessor.byteOffset + i * stride),
                            elem_size, i * elem_size)){
            LOG(ERR) << "Can not fill buffer.";
            continue;
        }
    }

    return buffer;
}