#pragma once

#include <variant>

#include "glw/Object.hpp"
#include "glw/Tex2D.hpp"

#include "Graphics/Render/Base/Vertex.hpp"

namespace Graphics::Render::Base {

class Primitive {
public:
    Primitive(const std::vector<Vertex> &vertices){
        _gl_obj = std::make_unique<glw::Object<Vertex>>(vertices);
    };

    template<class I>
    Primitive(const std::vector<Vertex> &vertices,
              const std::vector<I> &indices){
        _gl_obj = std::make_unique<glw::ObjectIndexed<Vertex>>(vertices, indices);
    };

    Primitive(const Primitive &) = delete;
    Primitive(Primitive &&prim) = default;
    virtual ~Primitive() = default;

    inline void draw() const {
        _gl_obj->draw(gl_draw_mode);
    }

    glw::DrawMode gl_draw_mode = glw::DrawMode::Triangles;

protected:
    std::unique_ptr<glw::Object<Vertex>> _gl_obj;
};

}