#pragma once 

#include <vector>

#include "Data/glTF.h"
#include "Data/BufferReceive/BufferCpu.h"
#include "Data/BufferReceive/BufferVertexGL.h"
#include "Data/BufferReceive/BufferElementGL.h"

namespace Graphics {

class gltfBufferReceiver {
public:
    gltfBufferReceiver();
    virtual ~gltfBufferReceiver();

    std::vector<std::shared_ptr<Buffer>> receive(const tinygltf::Model &model);
};

}