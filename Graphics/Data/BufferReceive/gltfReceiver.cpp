#include "Data/BufferReceive/gltfReceiver.h"

#include "Data/glTF.h"

#include "Log.h"

using namespace Graphics;

gltfBufferReceiver::gltfBufferReceiver(){

}

gltfBufferReceiver::~gltfBufferReceiver(){

}

std::vector<std::shared_ptr<Buffer>> gltfBufferReceiver::receive(const tinygltf::Model &model){
    std::vector<std::shared_ptr<Buffer>> list;

    for (auto &accesor : model.accessors){
        auto &view = model.bufferViews[accesor.bufferView];
        auto &data = model.buffers[view.buffer];

        ComponentType data_type = glTF::getComponentType(accesor.componentType);
        ComponentSize data_size = glTF::getComponentSize(accesor.type);
        size_t elem_size = accesor.type * glTF::getComponentTypeSize(data_type);
        size_t stride = view.byteStride == 0 ? elem_size : view.byteStride;

        std::shared_ptr<Buffer> buffer;
        list.push_back(buffer);

        if (view.target == TINYGLTF_TARGET_ARRAY_BUFFER){
            buffer = std::make_shared<BufferVertexGL>(data_type, data_size,
                                                      accesor.count * elem_size);
        } else if (view.target == TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER){
            buffer = std::make_shared<BufferElementGL>(data_type, data_size,
                                                      accesor.count * elem_size);
        } else {
            buffer = std::make_shared<BufferCpu>(data_type, data_size,
                                                      accesor.count * elem_size);
        }

        for (auto i = 0; i < accesor.count; i++){
            if (!buffer->write(&data.data.at(view.byteOffset + accesor.byteOffset + i * stride),
                                elem_size, i * elem_size)){
                LOG(ERR) << "Can not fill buffer.";
                continue;
            }
        }
    }
}