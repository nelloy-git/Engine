#pragma once

#include "GLwrap/Tex2D.h"

namespace Graphics::Render::Base {

using Texture = GLwrap::Tex2D;


class Material {

public:
    Material() = default;
    virtual ~Material() = default;

    struct TexInfo {
        explicit TexInfo() = default;
        Texture *texture = nullptr;
        // Multiplicator for pixels
        float scale[4] = {0.0, 0.0, 0.0, 0.0};
    };

    enum class LayerType {
        Color,
        PBR,
        NORMAL,
        Occlusion,
        Emissive
    };

    TexInfo *addLayerInfo(LayerType type, size_t layer){
        auto type_n = static_cast<size_t>(type);

        if (type_n >= _info.size()){
            _info.resize(type_n + 1);
        }

        if (layer >= _info[type_n].size()){
            _info.resize(layer + 1);
        }

        if (!_info[type_n][layer]){
            _info[type_n][layer] = std::make_unique<TexInfo>();
        }

        return _info[type_n][layer].get();
    };

    TexInfo *getLayerInfo(LayerType type, size_t layer){
        auto type_n = static_cast<size_t>(type);

        if (type_n >= _info.size() || layer >= _info[type_n].size() || !_info[type_n][layer]){
            return nullptr;
        }

        return _info[type_n][layer].get();
    }

    // TexInfo color;
    // TexInfo pbr{layer = 1};
    // TexInfo normal{layer = 2};
    // TexInfo occlusion{layer = 3};
    // TexInfo emissive{layer = 4};

private:
    std::vector<std::vector<std::unique_ptr<TexInfo>>> _info;

};

}