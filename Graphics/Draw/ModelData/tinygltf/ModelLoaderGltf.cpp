#include "Draw/ModelData/tinygltf/ModelLoaderGltf.hpp"

#include <type_traits>

#include "tiny_gltf.h"
#include "Draw/ModelData/tinygltf/TypesGltf.h"

#include "Log.h"

using namespace Graphics::Draw;

ModelLoaderGltf::ModelLoaderGltf() :
    ModelLoader(){
}

ModelLoaderGltf::~ModelLoaderGltf(){
}

void ModelLoaderGltf::load(Model &dst,
                           const std::string &path,
                           std::vector<std::string> &errors) const {
    auto gltf_model = _loadGltfModel(path, errors);
    if (!gltf_model){
        return;
    }

    _iterate<Buffer>(gltf_model->accessors, *gltf_model, &ModelLoaderGltf::_loadBuffer, dst, errors);
    _iterate<Texture>(gltf_model->textures, *gltf_model, &ModelLoaderGltf::_loadTexture, dst, errors);
    _iterate<Material>(gltf_model->materials, *gltf_model, &ModelLoaderGltf::_loadMaterial, dst, errors);
    _iterate<Mesh>(gltf_model->meshes, *gltf_model, &ModelLoaderGltf::_loadMesh, dst, errors);
    _iterate<Node>(gltf_model->nodes, *gltf_model, &ModelLoaderGltf::_loadNode, dst, errors);
    _iterate<Scene>(gltf_model->scenes, *gltf_model, &ModelLoaderGltf::_loadScene, dst, errors);
    _iterate<Animation>(gltf_model->animations, *gltf_model, &ModelLoaderGltf::_loadAnimation, dst, errors);
    _linkNodes(*gltf_model, dst, errors);
}

std::shared_ptr<tinygltf::Model>
ModelLoaderGltf::_loadGltfModel(const std::string &path,
                                std::vector<std::string> &errors) const {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    auto model = std::make_shared<tinygltf::Model>();

    bool res = loader.LoadASCIIFromFile(model.get(), &err, &warn, path);
    if (!warn.empty()) {
        errors.push_back(warn);
    }

    if (!err.empty()) {
        errors.push_back(err);
    }

    if (!res){
        errors.push_back("failed to load glTF: " + path);
        return nullptr;
    }

    return model;
}

void
ModelLoaderGltf::_loadBuffer(const tinygltf::Accessor &gltf_accessor,
                             const tinygltf::Model &gltf_model,
                             Model &model,
                             std::vector<std::string> &errors) const{

    auto &view = gltf_model.bufferViews[gltf_accessor.bufferView];
    auto &data = gltf_model.buffers[view.buffer];

    auto elem_type = gltfConvert::getBufferElemType(gltf_accessor.componentType);
    if (elem_type == BufferElemType::Unknown){
        errors.push_back("got unknown buffer element type (" + toString(elem_type) + ").");
        return;
    }

    auto elem_struct = gltfConvert::getBufferElemStruct(gltf_accessor.type);
    if (elem_struct == BufferElemStruct::Unknown){
        errors.push_back("got unknown buffer element struct (" + toString(elem_struct) + ").");
        return;
    }

    size_t elem_size = getSize(elem_struct) * getSize(elem_type);
    size_t stride = view.byteStride == 0 ? elem_size : view.byteStride;

    auto type = gltfConvert::getBufferType(view.target);
    auto buffer = model.addBuffer(type, elem_type, elem_struct,
                                  gltf_accessor.count,
                                  gltf_accessor.count * elem_size,
                                  gltf_accessor.normalized);

    for (auto i = 0; i < gltf_accessor.count; i++){
        if (!buffer->write(&data.data.at(view.byteOffset + gltf_accessor.byteOffset + i * stride),
                            i * stride, elem_size)){
            errors.push_back("writing error.");
            return;
        }
    }
}

void
ModelLoaderGltf::_loadTexture(const tinygltf::Texture &gltf_tex,
                              const tinygltf::Model &gltf_model,
                              Model &model,
                              std::vector<std::string> &errors) const{

    auto &sampler = gltf_model.samplers[gltf_tex.sampler];
    auto &image = gltf_model.images[gltf_tex.source];

    auto tex = model.addTexture(image.width, image.height, image.component, image.bits);
    tex->write(&image.image.at(0), 0, 0, image.width, image.height);

    tex->wrap_s = gltfConvert::getTextureWrap(sampler.wrapS);
    tex->wrap_t = gltfConvert::getTextureWrap(sampler.wrapT);
    
    if (sampler.minFilter > 0){
        tex->min_filter = gltfConvert::getTextureFilter(sampler.minFilter);
    }
    
    if (sampler.magFilter > 0){
        tex->mag_filter = gltfConvert::getTextureFilter(sampler.magFilter);
    }
}

void
ModelLoaderGltf::_loadMaterial(const tinygltf::Material &gltf_material,
                               const tinygltf::Model &gltf_model,
                               Model &model,
                               std::vector<std::string> &errors) const{

    auto mater = model.addMaterial();
                                                 
    for (int i = 0; i < 4; i++){
        mater->base_color[i] = (float)gltf_material.pbrMetallicRoughness.baseColorFactor[i];
    }

    auto index = gltf_material.pbrMetallicRoughness.baseColorTexture.index;
    mater->base_texture = model.textures()[index];

    if (!mater->base_texture){
        errors.push_back("texture[" + std::to_string(index) + "] is not initialized.");
    }
}

void
ModelLoaderGltf::_loadMesh(const tinygltf::Mesh &gltf_mesh,
                           const tinygltf::Model &gltf_model,
                           Model &model,
                           std::vector<std::string> &errors) const{
    auto mesh = model.addMesh();
    for (int i = 0; i < gltf_mesh.primitives.size(); ++i){
        _loadPrimitive(gltf_mesh.primitives[i], gltf_model, model, *mesh, errors);
    }

    auto &gltf_weights = gltf_mesh.weights;
    for (int i = 0; i < gltf_weights.size(); ++i){
        mesh->weights.push_back(gltf_weights[i]);
    }
}

void
ModelLoaderGltf::_loadPrimitive(const tinygltf::Primitive &gltf_prim,
                                const tinygltf::Model &gltf_model,
                                const Model &model,
                                Mesh &mesh,
                                std::vector<std::string> &errors) const{

    auto prim = mesh.addPrimitive();

    prim->mode = gltfConvert::getDrawMode(gltf_prim.mode);
    if (prim->mode == PrimitiveDrawMode::Unknown){
        errors.push_back("got unknown primitive draw mode (" + std::to_string(gltf_prim.mode) + ").");
        return;
    }

    if (gltf_prim.indices >= 0){
        prim->indices = model.buffers()[gltf_prim.indices];
        if (!prim->indices || prim->indices->type != BufferType::Index){
            errors.push_back("invalid index array type (buffer[" + std::to_string(gltf_prim.indices) + "]).");
            return;
        }
    }

    if (gltf_prim.material >= 0){
        prim->material = model.materials()[gltf_prim.material];
        if (!prim->material){
            errors.push_back("material is not initialized (material[" + std::to_string(gltf_prim.material) + "]).");
            return;
        }
    }

    for (auto iter : gltf_prim.attributes){
        auto attr = gltfConvert::getAttribute(iter.first);
        if (attr == PrimitiveAttribute::Unknown){
            errors.push_back("got unknown attribute name (" + iter.first + ").");
            continue;
        }

        auto buff = model.buffers()[iter.second];
        if (!buff || buff->type != BufferType::Vertex){
            errors.push_back("got wrong buffer type (buffer[" + std::to_string(iter.second) + "]).");
            continue;
        }

        prim->attributes[attr] = buff;
    }

    for (int i = 0; i < gltf_prim.targets.size(); i++){
        auto &list = gltf_prim.targets[i];

        std::shared_ptr<Buffer> pos;
        std::shared_ptr<Buffer> norm;
        std::shared_ptr<Buffer> tang;

        for (auto &iter : list){
            auto attr = gltfConvert::getAttribute(iter.first);
            auto buff = model.buffers()[iter.second];
            switch (attr){
                case PrimitiveAttribute::Position:
                    pos = buff;
                    break;

                case PrimitiveAttribute::Normal:
                    norm = buff;
                    break;

                case PrimitiveAttribute::Tangent:
                    tang = buff;
                    break;

                default:
                    errors.push_back("got unknown target attribute (" + iter.first + ").");
                    continue;
            }
        }
            
        prim->morph_targets.push_back({pos, norm, tang});
    }

    prim->init();
}

void
ModelLoaderGltf::_loadNode(const tinygltf::Node &gltf_node,
                           const tinygltf::Model &gltf_model,
                           Model &model,
                           std::vector<std::string> &errors) const{
    std::shared_ptr<Node> node;

    if (gltf_node.matrix.size() != 0){
        if (gltf_node.matrix.size() == 16){
            glm::mat4 mat;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    mat[i][j] = gltf_node.matrix[i * 4 + j];
                }
            }
            node = model.addNode(mat);
        } else {
            errors.push_back("wrong matrix size.");
        }
    } else {
        glm::vec3 scale(1.f);
        if (gltf_node.scale.size() == 3){
            scale = {
                gltf_node.scale[0],
                gltf_node.scale[1],
                gltf_node.scale[2]
            };
        }

        glm::quat rot = {1.f, 0.f, 0.f, 0.f};
        if (gltf_node.rotation.size() == 4){
            rot = {
                (float)gltf_node.rotation[3], 
                (float)gltf_node.rotation[0], 
                (float)gltf_node.rotation[1], 
                (float)gltf_node.rotation[2]
            };
        }

        glm::vec3 trans(0.f);
        if (gltf_node.translation.size() == 3){
            trans = {
                gltf_node.translation[0],
                gltf_node.translation[1],
                gltf_node.translation[2]};
        }

        node = model.addNode(trans, rot, scale);
    }

    if (gltf_node.mesh >= 0){
        node->mesh = model.meshes()[gltf_node.mesh];
    }
}

void 
ModelLoaderGltf::_linkNodes(const tinygltf::Model &gltf_model,
                            Model &model,
                            std::vector<std::string> &errors) const{

    for (int i = 0; i < gltf_model.nodes.size(); i++){
        auto &gltf_node = gltf_model.nodes[i];
        auto node = model.nodes()[i];

        if (node->children.size() > 0){
            continue;
        }

        for (int j = 0; j < gltf_node.children.size(); j++){
            auto child = model.nodes()[gltf_node.children[j]];
            node->children.push_back(child);

            if (child->parent){
                errors.push_back("Node[" + std::to_string(j) + "] can have only one parent.");
                continue;
            }

            child->parent = node;
        }
    }
}

void
ModelLoaderGltf::_loadScene(const tinygltf::Scene &gltf_scene,
                            const tinygltf::Model &gltf_model,
                            Model &model,
                            std::vector<std::string> &errors) const{
    auto scene = model.addScene();

    for (int i = 0; i < gltf_scene.nodes.size(); i++){
        int node_pos = gltf_scene.nodes[i];
        scene->nodes.push_back(model.nodes()[node_pos]);
    }
}

void
ModelLoaderGltf::_loadAnimation(const tinygltf::Animation &gltf_anim,
                                const tinygltf::Model &gltf_model,
                                Model &model,
                                std::vector<std::string> &errors) const{
    auto anim = model.addAnimation();

    for (int i = 0; i < gltf_anim.channels.size(); ++i){
        auto &gltf_chan = gltf_anim.channels[i];        
        _loadAnimationChannel(gltf_chan, gltf_anim, gltf_model, model, *anim, errors);
    }
}

void 
ModelLoaderGltf::_loadAnimationChannel(const tinygltf::AnimationChannel &gltf_chan,
                                       const tinygltf::Animation &gltf_anim,
                                       const tinygltf::Model &gltf_model,
                                       const Model &model,
                                       Animation &anim,
                                       std::vector<std::string> &errors) const{
    
    auto &time_buffer = model.buffers().at(gltf_anim.samplers[gltf_chan.sampler].input);
    auto &data_buffer = model.buffers().at(gltf_anim.samplers[gltf_chan.sampler].output);

    std::shared_ptr<AnimationChannel> chan;
    auto &gltf_targ = gltf_chan.target_path;
    if (gltf_targ == "translation"){
        auto trans_chan = std::make_shared<AnimationChannelTranslate>();
        anim.translations.push_back(trans_chan);
        chan = trans_chan;

        trans_chan->data.reserve(data_buffer->count);
        float buf[3];
        for (int j = 0; j < data_buffer->count; ++j){
            data_buffer->read(buf, j * 3 * sizeof(float), 3 * sizeof(float));
            std::cout << buf[0] << ", " << buf[1] << ", " << buf[2] << std::endl;
            trans_chan->data.push_back(glm::vec3(buf[0], buf[1], buf[2]));
        }

    } else if (gltf_targ == "rotation"){
        auto rot_chan = std::make_shared<AnimationChannelRotate>();
        anim.rotations.push_back(rot_chan);
        chan = rot_chan;

        rot_chan->data.reserve(data_buffer->count);
        float buf[4];
        for (int j = 0; j < data_buffer->count; ++j){
            data_buffer->read(buf, j * 3 * sizeof(float), 3 * sizeof(float));
            rot_chan->data.push_back({buf[0], buf[1], buf[2], buf[3]});
        }

    } else if (gltf_targ == "scale"){
        auto scale_chan = std::make_shared<AnimationChannelScale>();
        anim.scales.push_back(scale_chan);
        chan = scale_chan;

        scale_chan->data.reserve(data_buffer->count);
        float buf[3];
        for (int j = 0; j < data_buffer->count; ++j){
            data_buffer->read(buf, j * 3 * sizeof(float), 3 * sizeof(float));
            scale_chan->data[j] = glm::vec3(buf[0], buf[1], buf[2]);
        }

    } else if (gltf_targ == "weights") {
        auto weight_chan = std::make_shared<AnimationChannelWeight>();
        anim.weights.push_back(weight_chan);
        chan = weight_chan;

        weight_chan->data.reserve(data_buffer->count);
        auto &gltf_mesh = gltf_model.meshes[gltf_model.nodes[gltf_chan.target_node].mesh];

        auto weights_count = gltf_mesh.weights.size();
        for (int j = 0; j < data_buffer->count; ++j){
            weight_chan->data.push_back({});
            for (int k = 0; k < weights_count; ++k){
                float cur;
                data_buffer->read(&cur, j * weights_count * sizeof(float), sizeof(float));
                weight_chan->data[j].push_back(cur);
            }
        }

    } else {
        errors.push_back("unknown animation data type \"" + gltf_targ + "\"");
        return;
    }
    
    chan->node = model.nodes()[gltf_chan.target_node];
    float buf;
    for (int i = 0; i < time_buffer->count; ++i){
        time_buffer->read(&buf, i * sizeof(float), sizeof(float));
        if ((gltf_targ == "translation")){
            std::cout << "Time: " << buf << std::endl;
        }
        chan->time.push_back(buf);
    }
}