#pragma once

#include <optional>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Draw/Model.h"
#include "Property.h"

namespace Graphics::Draw {

class Object {
public:
    Object();
    virtual ~Object();

    const Property<glm::mat4, Object> matrix;
    Property<glm::vec3, Object> translation;
    Property<glm::quat, Object> rotation;
    Property<glm::vec3, Object> scale;

private:

};

}