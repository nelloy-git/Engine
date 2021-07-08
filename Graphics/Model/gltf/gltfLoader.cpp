#include "Model/gltf/gltfLoader.h"

#include "Model/gltf/gltf.h"

#include "Log.h"

using namespace Graphics::Model;

std::shared_ptr<Model> gltfLoader::load(const std::string &path){
    auto data = _loadGltfModel(path);
    _result = std::make_shared<Model>();

    for (int i = 0; i < data->accessors.size(); i++){
        auto &accessor = data->accessors[i];
        _result->buffers.push_back(_loadBuffer(accessor, *data));
    }

    for (int i = 0; i < data->textures.size(); i++){
        auto &texture = data->textures[i];
        _result->textures.push_back(_loadTexture(texture, *data));
    }

    for (int i = 0; i < data->materials.size(); i++){
        auto material = data->materials[i];
        _result->materials.push_back(_loadMaterial(material, *data));
    }

    for (int i = 0; i < data->meshes.size(); i++){
        auto &mesh = data->meshes[i];
        _result->meshes.push_back(_loadMesh(mesh, *data));
    }

    auto res = _result;
    _result = nullptr;
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

    auto data_type = gltfConvert::getBufferElemType(accessor.componentType);
    if (data_type == BufferElemType::Unknown){
        LOG(ERR) << "BufferElemType::Unknown";
        return nullptr;
    }

    auto data_size = gltfConvert::getBufferElemSize(accessor.type);
    if (data_size == BufferElemStruct::Unknown){
        LOG(ERR) << "BufferElemStruct::Unknown";
        return nullptr;
    }

    size_t elem_size = static_cast<int>(data_size) * getSize(data_type);
    size_t stride = view.byteStride == 0 ? elem_size : view.byteStride;

    auto type = gltfConvert::getBufferType(view.target);
    auto buffer = Creator::newBuffer(type, data_type, data_size,
                                     accessor.normalized, accessor.count,
                                     accessor.count * elem_size);

    for (auto i = 0; i < accessor.count; i++){
        if (!buffer->write(&data.data.at(view.byteOffset + accessor.byteOffset + i * stride),
                            elem_size, i * elem_size)){
            LOG(ERR) << "Can not fill buffer.";
            continue;
        }
    }

    return buffer;
}

std::shared_ptr<Material> gltfLoader::_loadMaterial(const tinygltf::Material &material,
                                                    const tinygltf::Model &model){

    auto mater = std::make_shared<Material>();
                                                 
    for (int i = 0; i < 4; i++){
        mater->base_color[i] = (float)material.pbrMetallicRoughness.baseColorFactor[i];
    }
    mater->base_texture = _result->textures[material.pbrMetallicRoughness.baseColorTexture.index];
    
    return mater;
}

std::shared_ptr<Texture> gltfLoader::_loadTexture(const tinygltf::Texture &gltf_tex,
                                                       const tinygltf::Model &model){
    auto &sampler = model.samplers[gltf_tex.sampler];
    auto &image = model.images[gltf_tex.source];

    auto tex = Creator::newTexture(image.width, image.height, image.component, image.bits);
    tex->wrap_s = gltfConvert::getTextureWrap(sampler.wrapS);
    tex->wrap_t = gltfConvert::getTextureWrap(sampler.wrapT);
    tex->min_filter = gltfConvert::getTextureFilter(sampler.minFilter);
    tex->mag_filter = gltfConvert::getTextureFilter(sampler.magFilter);

    return tex;
}

std::shared_ptr<Mesh> gltfLoader::_loadMesh(const tinygltf::Mesh &mesh,
                                            const tinygltf::Model &model){
    auto res = std::make_shared<Mesh>();

    for (int i = 0; i < mesh.primitives.size(); i++){
        auto prim = _loadPrimitive(mesh.primitives[i], model);
        res->primitives.push_back(prim);
    }

    return res;
}

std::shared_ptr<Primitive> gltfLoader::_loadPrimitive(const tinygltf::Primitive prim,
                                                      const tinygltf::Model &model){

    auto res = Creator::newPrimitive();

    res->mode = gltfConvert::getDrawMode(prim.mode);
    if (res->mode == PrimitiveDrawMode::Unknown){
        LOG(ERR) << "res->mode == PrimitiveDrawMode::Unknown";
        return nullptr;
    }

    if (prim.indices > 0){
        res->indices = _result->buffers[prim.indices];
        if (!res->indices || res->indices->type != BufferType::Index){
            LOG(ERR) << "!res->indices || res->indices->type != BufferType::Index";
            return nullptr;
        }
    }

    if (prim.material > 0){
        res->material = _result->materials[prim.material];
        if (!res->material){
            LOG(ERR) << "!res->material";
            return nullptr;
        }
    }

    for (auto iter : prim.attributes){
        auto attr = gltfConvert::getAttribute(iter.first);
        if (attr == PrimitiveAttribute::Unknown){
            LOG(ERR) << "attr == PrimitiveAttribute::Unknown";
            continue;
        }

        auto buff = _result->buffers[iter.second];
        if (!buff || buff->type != BufferType::Vertex){
            LOG(ERR) << "!buff || buff->type != BufferType::Vertex";
            continue;
        }

        res->attributes[attr] = buff;
    }

    for (int i = 0; i < prim.targets.size(); i++){
        auto &list = prim.targets[i];

        std::shared_ptr<Buffer> pos;
        std::shared_ptr<Buffer> norm;
        std::shared_ptr<Buffer> tang;

        for (auto &iter : list){
            auto attr = gltfConvert::getAttribute(iter.first);
            auto buff = _result->buffers[iter.second];
            switch (attr){
                case PrimitiveAttribute::Position:
                    pos = buff;
                    break;

                case PrimitiveAttribute::Normal:
                    norm = buff;
                    break;

                case PrimitiveAttribute::Tangent:
                    norm = buff;
                    break;

                default:
                    LOG(ERR) << "wrong target attribute.";
                    continue;
            }
        }
            
        res->targets.push_back({pos, norm, tang});
    }

    res->update();
    return res;
}