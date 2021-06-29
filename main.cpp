#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <memory>
 
#include "GLwrap/Program.h"
#include "GLwrap/Shader.h"

#include "Context/Timer.h"
#include "Context/Window.h"

#include "Data/Model.h"

#include "Drawing/Camera.h"
#include "Drawing/Drawer.h"

#include "Log.h"

using namespace Graphics;

const float cam_vel = 5;

std::shared_ptr<GLwrap::Program> initProgram(const std::string &vsh, const std::string &fsh){
    std::shared_ptr<GLwrap::Program> progr;

    auto vshader = GLwrap::Shader::fromFile(
        GLwrap::ShaderType::VERTEX, vsh);

    auto fshader = GLwrap::Shader::fromFile(
        GLwrap::ShaderType::FRAGMENT, fsh);

    if (!vshader || !fshader){
        return nullptr;
    }
    
    std::vector<std::shared_ptr<GLwrap::Shader>> shader_list;
    shader_list.push_back(vshader);
    shader_list.push_back(fshader);

    return std::make_shared<GLwrap::Program>(shader_list);
}



int main(int argc, const char** argv){
    int width = 640;
    int height = 480;
    bool running = true;

    auto window = std::make_unique<GLwrap::Window>(width, height, "Test");
    window->setActive(true);

    glEnable(GL_DEPTH_TEST);
    // window->setGlParam(GLwrap::WindowGLparam::DEPTH_TEST, true);

    window->onClose.add([&running](){
        running = false;
    });

    auto model3d = std::make_shared<Model>("../test/triang/triang.gltf");

    std::shared_ptr<GLwrap::Program> progr = initProgram("../shaders/base.vert", "../shaders/base.frag");
    if (!progr){return -1;}

    auto timer = std::make_shared<GLwrap::Timer>();
    timer->start();

    auto cam = std::make_shared<Graphics::Camera>();
    cam->width = width;
    cam->height = height;
    cam->pos = glm::vec3(-0.3, 0, 0);

    auto drawer = std::make_shared<Graphics::Drawer>(glm::vec2(0, 0), glm::vec2(width, height));
    drawer->setCamera(cam);
    drawer->setShader(progr);
    drawer->setActive(true);

    glm::vec4 back_color(0.2f, 0.3f, 0.3f, 1.0f);
    glm::mat4 model_pos(1.0f);
    model_pos = glm::scale(model_pos, glm::vec3(0.1, 0.1, 0.1));
    // model_pos = glm::rotate<float>(model_pos, 3.14 / 2, glm::vec3(0, 1, 0));
    model_pos = glm::rotate<float>(model_pos, 3 * 3.1415 / 2, glm::vec3(0, 1, 0));

    float mx = width / 2;
    float my = height / 2;
    float mdx = 0;
    float mdy = 0;

    window->mouse.onMove.add([&mx, &my, &mdx, &mdy](double x, double y){
        mdx = x - mx;
        mdy = y - my;
        mx = x;
        my = y;
    });

    float last = 0;
    while (running){
        float dt = timer->elapsed();
        last += dt;
        timer->start();

        float dist = cam_vel * dt;

        if (window->keyboard.isDown(GLwrap::KeyboardKey::W)){
            cam->pos += cam->direction * dist;
        }

        if (window->keyboard.isDown(GLwrap::KeyboardKey::S)){
            cam->pos -= cam->direction * dist;
        }

        if (window->keyboard.isDown(GLwrap::KeyboardKey::D)){
            cam->pos += cam->right * dist;
        }

        if (window->keyboard.isDown(GLwrap::KeyboardKey::A)){
            cam->pos -= cam->right * dist;
        }

        drawer->clear(back_color);
        drawer->draw(*model3d, model_pos);
        
        window->swapBuffers();
        glfwPollEvents();

        if (last > 1){
            std::cout << cam->pos[0] << "; " << cam->pos[1] << "; " << cam->pos[2] << std::endl;
            last = 0;
        }
    }

    return 0;
}
 