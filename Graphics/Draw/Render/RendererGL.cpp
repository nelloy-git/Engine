#include "Draw/Render/RendererGL.hpp"

#include "glm/gtc/type_ptr.hpp"

using namespace Graphics::Render;

RendererGL::RendererGL(const VertexShaderGL &vert, const FragmentShaderGL &frag){
    std::vector<const GLwrap::Shader *> list {
        vert.gl.get(),
        frag.gl.get()
    };
    gl = std::make_unique<GLwrap::Program>(list);
}

RendererGL::~RendererGL(){
}

void RendererGL::draw(const PrimitiveGL &primitive,
                      const glm::mat4 &pose,
                      const std::vector<float> &morph){
    
    gl->setUniformMat4f("pose", glm::value_ptr(pose));
    if (primitive.gl_indices){
        primitive.gl_object->drawElements(primitive.gl_draw_mode,
                                          primitive.gl_indices->data_type,
                                          primitive.gl_indices->count,
                                          0);
    }
}