#include "Data/Model/gltfModel.h"

#include "Log.h"
#include "Data/glTF.h"

#include "Data/BufferReceiver/gltfReceiver.h"

using namespace Graphics;

gltfModel::gltfModel(const std::string &path) :
    Model(path){

    auto gltf_model = _loadGltfModel(path);

    for (auto &gltf_tex : gltf_model->textures){
        textures.push_back(_loadTexture(gltf_tex, *gltf_model));
    }

    for (auto &gltf_material : gltf_model->materials){
        materials.push_back(_loadMaterial(gltf_material ));
    }
    
    gltfBufferReceiver buffer_receiver;
    buffers = buffer_receiver.receive(*gltf_model);

    // Meshes
    for (auto &gltf_mesh : gltf_model->meshes){
        meshes.push_back(_loadMesh(gltf_mesh, *gltf_model));
    }

    // Nodes
    for (auto &gltf_node : gltf_model->nodes){
        nodes.push_back(_loadNode(gltf_node, *gltf_model));
    }
    // Set mesh and children
    for (int i = 0; i < nodes.size(); i++){
        auto &gltf_node = gltf_model->nodes[i];

        auto node = nodes[i];
        if (gltf_node.mesh >= 0){
            node->mesh = meshes[gltf_node.mesh];
        }
        
        for (int child : gltf_node.children){
            nodes[child]->parent = node;
            node->children.push_back(nodes[child]);
        }
    }


    delete gltf_model;
}

gltfModel::~gltfModel(){

}

tinygltf::Model *gltfModel::_loadGltfModel(const std::string &path){
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
        throw std::invalid_argument(err);
    }

    if (!res){
        err = "failed to load glTF: " + path;
        LOG(ERR) << err;
        throw std::invalid_argument(err);
    }

    return model;
}

std::shared_ptr<Node> gltfModel::_loadNode(const tinygltf::Node &gltf_node,
                                           const tinygltf::Model &gltf_model){

    std::shared_ptr<Node> node;
    
    if (gltf_node.matrix.size() != 0){
        if (gltf_node.matrix.size() == 16){
            glm::mat4 mat;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    mat[i][j] = gltf_node.matrix[i * 4 + j];
                }
            }
            node = std::make_shared<Node>(mat);
        } else {
            LOG(WRN) << "wrong matrix size.";
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

        node = std::make_shared<Node>(trans, rot, scale);
    }

    return node;
}

std::shared_ptr<Mesh> gltfModel::_loadMesh(const tinygltf::Mesh &gltf_mesh,
                                           const tinygltf::Model &gltf_model){
    auto mesh = std::make_shared<Mesh>();

    for (auto &gltf_prim : gltf_mesh.primitives){
        auto prim = _loadPrimitive(gltf_prim);
        mesh->primitives.push_back(prim);
        prim->material = materials[gltf_prim.material];
    }

    return mesh;
}

std::shared_ptr<Primitive> gltfModel::_loadPrimitive(const tinygltf::Primitive &gltf_prim){

    auto gl_indices = std::dynamic_pointer_cast<BufferElementGL>(buffers[gltf_prim.indices]);

    if (!gl_indices){
        LOG(WRN) << "Wrong indices buffer type.";
        return nullptr;
    }

    std::unordered_map<int, std::shared_ptr<BufferVertexGL>> attributes;
    for (auto &attr : gltf_prim.attributes){
        int loc;
        try {
            loc = glTF::getLayoutLocation(attr.first);
        } catch (std::exception e){
            LOG(WRN) << "Unknown attribute name " << attr.first;
            continue;
        }

        auto gl_buffer = std::dynamic_pointer_cast<BufferVertexGL>(buffers[attr.second]);
        if (!gl_buffer){
            LOG(WRN) << "Wront attribute buffer type.";
            continue;
        }

        attributes[loc] = gl_buffer;
    }

    auto mode = glTF::getDrawMode(gltf_prim.mode);

    return std::make_shared<Primitive>(gl_indices, attributes, mode);
}

std::shared_ptr<Material> gltfModel::_loadMaterial(const tinygltf::Material &gltf_material){
    auto mater = std::make_shared<Material>();
                                                 
    for (int i = 0; i < 4; i++){
        mater->base_color[i] = (float)gltf_material.pbrMetallicRoughness.baseColorFactor[i];
    }
    mater->base_texture = textures[gltf_material.pbrMetallicRoughness.baseColorTexture.index];
    
    return mater;
}


std::shared_ptr<GLwrap::Tex2D> gltfModel::_loadTexture(const tinygltf::Texture &gltf_tex,
                                                       const tinygltf::Model &model){
    auto &sampler = model.samplers[gltf_tex.sampler];
    auto &image = model.images[gltf_tex.source];

    std::vector<std::pair<GLwrap::Tex2DParamInt, GLuint>> sampler_params = {
        {GLwrap::Tex2DParamInt::WRAP_S, glTF::getImageWrap(sampler.wrapS)},
        {GLwrap::Tex2DParamInt::WRAP_T, glTF::getImageWrap(sampler.wrapT)},
    };

    auto tex = std::make_shared<GLwrap::Tex2D>();
    tex->load(&image.image.at(0), image.width, image.height,
              GLwrap::Tex2DinternalFormat::RGBA,
              glTF::getImageFormat(image.component),
              image.bits == 8 ? GLwrap::Tex2DpixelType::UNSIGNED_BYTE : GLwrap::Tex2DpixelType::UNSIGNED_SHORT,
              sampler_params
    );

    return tex;
}

