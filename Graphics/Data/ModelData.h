#pragma once

#include <map>
#include <vector>

#include "GLwrap/Buffer.h"
#include "GLwrap/Tex2D.h"

#include "Data/glTF.h"
#include "Data/BufferView.h"
#include "Data/Mesh.h"
#include "Data/Node.h"
#include "Data/Scene.h"

namespace Graphics {

class ModelData {
public:
    ModelData(std::shared_ptr<tinygltf::Model> model);
    virtual ~ModelData();

    std::shared_ptr<Scene> getScene(int pos);
    std::shared_ptr<Node> getNode(int pos);
    std::shared_ptr<Mesh> getMesh(int pos);

    std::shared_ptr<BufferView> getBufferView(int pos);
    std::shared_ptr<Accessor> getAccessor(int pos);

private:

    std::shared_ptr<tinygltf::Model> _model;

    std::map<int, std::shared_ptr<Scene>> _scenes;
    std::map<int, std::shared_ptr<Node>> _nodes;
    std::map<int, std::shared_ptr<Mesh>> _meshes;

    std::map<int, std::shared_ptr<BufferView>> _buffer_views;
    std::map<int, std::shared_ptr<Accessor>> _accessors;

    std::map<int, std::shared_ptr<GLwrap::Tex2D>> _textures;

    template<typename T, typename P>
    auto _getData(int pos, std::map<int, std::shared_ptr<T>> map, const P &tiny_data){
        auto iter = map.find(pos);
        if (iter == map.end()){
            map[pos] = std::make_shared<T>(tiny_data, *this);
            iter = map.find(pos);
        }
        return iter->second;
    }

};

}

// 5труба+8текстиль+16трактор+8.5песок+17щебень+3работник