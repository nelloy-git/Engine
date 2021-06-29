#include "Data/BufferView.h"

#include "Data/ModelData.h"

using namespace Graphics;

BufferView::BufferView(const tinygltf::Model &model,
                       const tinygltf::BufferView &view,
                       ModelData &data){
    
    const static auto VERTEX_ARRAY = GLwrap::BufferType::ARRAY;
    const static auto INDEX_ARRAY = GLwrap::BufferType::ELEMENT_ARRAY;

    bool is_vertex = view.target == TINYGLTF_TARGET_ARRAY_BUFFER;
    buffer = std::make_shared<GLwrap::Buffer>(
                is_vertex ? VERTEX_ARRAY : INDEX_ARRAY,
                view.byteLength
             );
    buffer->load(&model.buffers[view.buffer].data.at(view.byteOffset));
}