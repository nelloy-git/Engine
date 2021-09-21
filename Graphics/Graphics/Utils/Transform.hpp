#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Property.hpp"

namespace Graphics {

class Transform {
public:
    Transform();
    explicit Transform(const glm::mat4 &mat);
    Transform(const glm::vec3 &trans,
              const glm::quat &rot,
              const glm::vec3 &scale);
    Transform(const Transform &other);
    virtual ~Transform();

    // Apply translation, rotation and scale (M = T * R * S).
    // Overrides current transform matrix if translation, rotation or scale were changed.
    void applyTRS();

    inline void setT(const glm::vec3 &trans){
        _trans = trans;
        _changed = true;
    }

    inline const glm::vec3 &getT(){
        return _trans;
    }

    inline void setR(const glm::quat &rot){
        _rot = rot;
        _changed = true;
    }

    inline const glm::quat getR(){
        return _rot;
    }

    inline void setS(const glm::vec3 &scale){
        _scale = scale;
        _changed = true;
    }

    inline const glm::vec3 getS(){
        return _scale;
    }
    
    glm::mat4 mat;

private:
    bool _changed;
    glm::vec3 _trans;
    glm::quat _rot;
    glm::vec3 _scale;

};

}