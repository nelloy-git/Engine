#include "Draw/ModelData/IFaces/Buffer.hpp"

using namespace Graphics::Draw;

Buffer::Buffer(const Model &model, int index,
               BufferType type, BufferElemType data_type, BufferElemStruct data_struct,
               size_t count, size_t bytes, bool normalized) :
        model(model),
        index(index),
        type(type), 
        data_type(data_type),
        data_size(data_size),
        count(count),
        bytes(bytes),
        normalized(normalized){
};

Buffer::~Buffer(){
}