#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/ModelData/IFaces/Node.hpp"

namespace Graphics::Draw {

template<typename T>
struct AnimationData {
    std::vector<float> time;
    std::vector<T> data;
};

using AnimationDataTranslation = AnimationData<glm::vec3>;


struct AnimationDataRotation {
    std::vector<float> time;
    std::vector<glm::quat> rot;
};

struct AnimationDataScale {
    std::vector<float> time;
    std::vector<glm::vec3> scale;
};

struct AnimationDataWeight {
    std::vector<float> time;
    std::vector<glm::vec3> weight;
};

class Animation {
public:
    std::shared_ptr<Node> node;
};

}