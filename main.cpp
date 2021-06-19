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

std::shared_ptr<GLwrap::Program> initShader(){
    std::shared_ptr<GLwrap::Program> progr;
    try{
        auto vshader = std::make_shared<GLwrap::Shader>(
            GLwrap::ShaderType::VERTEX, "../shaders/base.vert");

        auto fshader = std::make_shared<GLwrap::Shader>(
            GLwrap::ShaderType::FRAGMENT, "../shaders/base.frag");
    
        std::vector<std::shared_ptr<GLwrap::Shader>> shader_list;
        shader_list.push_back(vshader);
        shader_list.push_back(fshader);

        progr = std::make_shared<GLwrap::Program>(shader_list);
    } catch (std::exception e){
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return progr;
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
    
    // Graphics::Model model3d("../test/book/scene.gltf");

    // tinygltf::Model model3d;
    // tinygltf::TinyGLTF loader;
    // std::string err;
    // std::string warn;
    // bool res = loader.LoadASCIIFromFile(&model3d, &err, &warn, "../test/book/scene.gltf");


    // Graphics::ModelBuffer buffer(model3d);

    // std::cout << "Meshes: " << model3d.meshes.size() << std::endl;
    // std::cout << "Primitives: " << model3d.meshes[i].primitives.size() << std::endl;
    // Graphics::Primitive prim(model3d, model3d.meshes[i].primitives[0], buffer);

    auto model3d = std::make_shared<Model>("../test/book/scene.gltf");

    std::shared_ptr<GLwrap::Program> progr = initShader();
    if (!progr){return -1;}

    auto timer = std::make_shared<GLwrap::Timer>();
    timer->start();

    auto cam = std::make_shared<Graphics::Camera>();
    cam->width = width;
    cam->height = height;

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

        // auto a = glm::vec3(0, 0, 0) - cam->pos;
        // glm::vec3 a = cam->pos * 3.;

        // glm::vec3 a = glm::vec3(0, 0, 0) - glm::vec3(0, 0, 0);
        // cam->direction = glm::normalize();

        // cam->yaw += 0.00005 * mdx;
        // cam->pitch += 0.00005 * mdy;

        drawer->clear(back_color);
        
        // model_pos = glm::rotate<float>(model_pos, dt, glm::vec3(0.f, 1.f, 0.f));
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
 