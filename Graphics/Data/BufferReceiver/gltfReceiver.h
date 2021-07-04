#pragma once 

#include <vector>

#include "Data/glTF.h"
#include "Data/Buffer/BufferCpu.h"
#include "Data/Buffer/BufferVertexGL.h"
#include "Data/Buffer/BufferElementGL.h"

namespace Graphics {

class gltfBufferReceiver {
public:
    gltfBufferReceiver();
    virtual ~gltfBufferReceiver();

    std::vector<std::shared_ptr<Buffer>> receive(const tinygltf::Model &model);
};

}