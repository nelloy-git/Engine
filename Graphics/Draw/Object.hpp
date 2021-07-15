#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Utils/Transform.hpp"
#include "Draw/Model.h"
#include "Property.hpp"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    Transform transform;

    Property<std::shared_ptr<Model>, Object> model;
    int active_scene = 0;

    void update();
    const glm::mat4 &getMatrix(const Node& node) const;

private:
    void _updateNodeMatrix(const Node &node);

    std::shared_ptr<Model> _model;
    const std::shared_ptr<Model> &_getModel();
    void _setModel(const std::shared_ptr<Model> &model);

    std::map<const Node *, glm::mat4> _matrices;
};

}