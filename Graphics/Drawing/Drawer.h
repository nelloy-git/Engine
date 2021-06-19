#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "GLwrap/Program.h"
#include "Data/Model.h"
#include "Drawing/Camera.h"

namespace Graphics {

class Drawer {
public:
    Drawer(glm::vec2 pos, glm::vec2 size);
    virtual ~Drawer();

    bool isActive();
    bool setActive(bool f);

    std::shared_ptr<Camera> camera();
    void setCamera(std::shared_ptr<Camera>);

    std::shared_ptr<GLwrap::Program> shader();
    void setShader(std::shared_ptr<GLwrap::Program> shader);

    bool clear(const glm::vec4 &color);
    bool draw(const Model &model, const glm::mat4 &pos);
    bool draw(const Primitive &primitive, const glm::mat4 &pos);

private:
    bool _active = false;
    glm::vec2 _pos;
    glm::vec2 _size;

    std::shared_ptr<Camera> _camera = nullptr;
    std::shared_ptr<GLwrap::Program> _shader = nullptr;

    static Drawer *_gl_active;
};

}