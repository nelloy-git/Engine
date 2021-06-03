#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "linmath.h"
 
#include <stdlib.h>
#include <stdio.h>
#include <memory>
 
#include "Window.h"
#include "VBO/Array.h"
#include "GLSL/Shader.h"
#include "GLSL/Program.h"
#include "GLSL/Attribute/VertexArray.h"

struct Vertices
{
    float x, y;
    float r, g, b;
};
 
std::string vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
std::string fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";
 
int main(int argc, const char** argv){
    
    auto window = new Graphics::Window(640, 480, "Test");
    window->setActive(true);
    
    gladLoadGL();
    glfwSwapInterval(0);
 
    // NOTE: OpenGL error checks have been omitted for brevity

    Vertices vertices[3] = {
        { -0.6f, -0.4f, 1.f, 0.f, 0.f },
        {  0.6f, -0.4f, 0.f, 1.f, 0.f },
        {   0.f,  0.6f, 0.f, 0.f, 1.f }
    };

    auto vbo = std::make_shared<Graphics::VBO::Array>();
    vbo->load(sizeof(Vertices[3]), &vertices, Graphics::VBO::UsageType::STATIC);

    auto vshader = std::make_shared<Graphics::GLSL::Shader>(
        Graphics::GLSL::ShaderType::VERTEX, vertex_shader_text);

    auto fshader = std::make_shared<Graphics::GLSL::Shader>(
        Graphics::GLSL::ShaderType::FRAGMENT, fragment_shader_text);
 
    std::vector<std::shared_ptr<Graphics::GLSL::Shader>> shader_list;
    shader_list.push_back(vshader);
    shader_list.push_back(fshader);

    auto progr = std::make_shared<Graphics::GLSL::Program>(shader_list);

    GLuint mvp_location = glGetUniformLocation(progr->id, "MVP");

    auto vpos = std::make_shared<Graphics::GLSL::Attribute::VertexArray>(
        progr, "vPos", vbo,
        Graphics::GLSL::DataSize::Vec2, Graphics::GLSL::DataType::Float, false, 
        sizeof(Vertices), 0
    );

    auto vcol = std::make_shared<Graphics::GLSL::Attribute::VertexArray>(
        progr, "vCol", vbo,
        Graphics::GLSL::DataSize::Vec3, Graphics::GLSL::DataType::Float, false, 
        sizeof(Vertices), 2 * sizeof(float)
    );

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    bool running = true;
    while (running){
        window->onClose.add([&running](){
            running = false;
        });

        float ratio;
        int width = 640;
        int height = 480;
        mat4x4 m, p, mvp;
 
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
 
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
 
        glUseProgram(progr->id);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

        window->swapBuffers();
        glfwPollEvents();
    }
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
 