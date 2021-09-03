#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <memory>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Context/Timer.h"
#include "Context/Window.h"

#include "Graphics/Render/RendererGL.hpp"

#include "Graphics/Utils/Camera.hpp"

#include "Log.h"

using namespace Graphics;

const float cam_vel = 5;
bool pause = false;

auto *initRender(){
    Render::VertexShaderGL vert;
    Render::FragmentShaderGL frag;

    return new Render::RendererGL(vert, frag);
}

void camMove(GLwrap::Window &window, Graphics::Draw::Camera &cam, float dist){
        
    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::W)){
        cam.pos += cam.direction * dist;
    }

    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::S)){
        cam.pos -= cam.direction * dist;
    }

    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::D)){
        cam.pos += cam.right * dist;
    }

    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::A)){
        cam.pos -= cam.right * dist;
    }

    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::SPACE)){
        cam.pos += cam.up * dist;
    }

    if (!pause && window.keyboard.isDown(GLwrap::KeyboardKey::LEFT_CONTROL)){
        cam.pos -= cam.up * dist;
    }

}

int main(int argc, const char** argv){
    int width = 640;
    int height = 480;
    bool running = true;

    auto window = std::make_unique<GLwrap::Window>(width, height, "Test");
    window->setActive(true);

    glEnable(GL_DEPTH_TEST);

    window->onClose.add([&running](){
        running = false;
    });


    auto cam = std::make_shared<Graphics::Draw::Camera>();
    cam->width = width;
    cam->height = height;
    cam->pos = glm::vec3(-0.3, 0, 0);

    auto timer = std::make_shared<GLwrap::Timer>();
    timer->start();

    glm::vec4 back_color(0.2f, 0.3f, 0.3f, 1.0f);
    glm::vec3 model_translation(0.f);
    glm::quat model_rotation = glm::angleAxis((float)(3 * 3.1415 / 2), glm::vec3(0, 1, 0));
    glm::vec3 model_scale = glm::vec3(1, 1, 1);

    auto s = glm::scale(glm::mat4(1.f), model_scale);
    auto r = glm::mat4_cast(model_rotation);
    auto t = glm::translate(glm::mat4(1.f), model_translation);
    glm::mat4 mat = t * r * s;

    float last = 0;
    float rot_vel = (float)(3.14 / 8);
    float angle = 0;

    window->keyboard.onPress.add([](GLwrap::KeyboardKey key, GLwrap::KeyMode mode){
        if (key == GLwrap::KeyboardKey::P){
            pause = !pause;
            std::cout << "Pressed" <<std::endl;
        }
    });

    auto renderer = initRender();
    auto prim = Render::PrimitiveGL::Cube();

    while (running){
        float dt = timer->elapsed();
        last += dt;
        timer->start();

        float dist = cam_vel * dt;
        camMove(*window, *cam, dist);

        glClearColor(back_color.x, back_color.y, back_color.z, back_color.w);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        auto clear_time = timer->elapsed();

        renderer->draw(*prim, cam->mat * mat, {});
        
        window->swapBuffers();
        glfwPollEvents();

        if (last > 1){
            std::cout << "================" << std::endl;
            std::cout << "Loop time: " << dt << std::endl;
            std::cout << "Clear time: " << clear_time << std::endl;
            // std::cout << "Update time: " << update_time << std::endl;
            // std::cout << "Draw time: " << draw_time << std::endl;
            std::cout << cam->pos[0] << "; " << cam->pos[1] << "; " << cam->pos[2] << std::endl;
            last = 0;
        }
    }

    return 0;
}
 