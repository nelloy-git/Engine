#pragma once

namespace Graphics::Model {

enum class Attribute : int {
    Position = 0,
    Normal = 1,
    Tangent = 2,
    TexCoord_0 = 3,
    TexCoord_1 = 4,
    Color_0 = 5,
    Joints_0 = 6,
    Joints_1 = 7,
    Weights_0 = 8,
    Weights_1 = 9,
};

constexpr inline const char *toString(Attribute attr);
constexpr inline int toInt(Attribute attr);

}