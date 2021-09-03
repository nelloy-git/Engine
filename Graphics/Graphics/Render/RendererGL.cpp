#include "Graphics/Render/RendererGL.hpp"

#include <iostream>

#include "glm/gtc/type_ptr.hpp"

using namespace Graphics::Render;

RendererGL::RendererGL(const VertexShaderGL &vert, const FragmentShaderGL &frag){
    std::vector<const GLwrap::Shader *> list {
        vert.gl.get(),
        frag.gl.get()
    };
    gl = std::make_unique<GLwrap::Program>(list);
    gl->use();
}

RendererGL::~RendererGL(){
}

void RendererGL::draw(const PrimitiveGL &primitive,
                      const glm::mat4 &pose,
                      const std::vector<float> &morph){
                          
    gl->setUniformMat4f("pose", glm::value_ptr(pose));
    primitive.gl_object->draw(primitive.gl_draw_mode);
}