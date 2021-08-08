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

#include "Draw/Utils/Camera.hpp"
#include "Draw/ModelData/tinygltf/ModelLoaderGltf.hpp"
#include "Draw/ModelData/GLwrap/ModelGL.hpp"
#include "Draw/ShaderGL.hpp"

// #include "Drawing/Camera.h"
// #include "Drawing/Drawer.h"

#include "Log.h"

using namespace Graphics;

const float cam_vel = 5;
bool pause = false;

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
    // window->setGlParam(GLwrap::WindowGLparam::DEPTH_TEST, true);

    window->onClose.add([&running](){
        running = false;
    });

    std::cout << Draw::toString<Draw::Node>() << std::endl;

    // std::shared_ptr<Model::Model> model3d = Model::Creator::newModel("../test/triang/triang.gltf");
    // std::shared_ptr<Draw::Model> model3d = Draw::Creator::newModel("../test/book/scene.gltf");
    // std::shared_ptr<Model::Model> model3d = Model::Creator::newModel("../test/ninja/scene.gltf");

    auto model_loader = std::make_shared<Draw::ModelLoaderGltf>();
    auto model_3d = std::make_shared<Draw::ModelGL>();
    auto shader = Draw::ShaderGL::fromFiles("../shaders/base.vert", "../shaders/base.frag");
    shader->verify();

    std::vector<std::string> errors;
    model_loader->load(*model_3d, "../test/book/scene.gltf", errors);
    if (errors.size() > 0){
        auto log = LOG(ERR);
        log << "Errors loading " << "../test/book/scene.gltf";
        for (auto &err : errors){
            log << err << "\n";
        }
    }

    auto cam = std::make_shared<Graphics::Draw::Camera>();
    cam->width = width;
    cam->height = height;
    cam->pos = glm::vec3(-0.3, 0, 0);


    std::vector<std::shared_ptr<Draw::Object>> objects;
    for (int i = 0; i < 1; ++i){
        auto object = std::make_shared<Draw::Object>();
        objects.push_back(object);
        object->setModel(model_3d);
        object->setCamera(cam);
        object->setScene(0);
        object->setAnimation(0);
        object->transform.setT(glm::vec3((float)i, 0.f, 0.f));
        object->transform.setR(glm::angleAxis((float)(3 * 3.1415 / 2), glm::vec3(0, 1, 0)));
        object->transform.setS(glm::vec3(0.1, 0.1, 0.1));
        object->transform.applyTRS();
    }

    auto timer = std::make_shared<GLwrap::Timer>();
    timer->start();

    glm::vec4 back_color(0.2f, 0.3f, 0.3f, 1.0f);
    glm::vec3 model_translation(0.f);
    glm::quat model_rotation = glm::angleAxis((float)(3 * 3.1415 / 2), glm::vec3(0, 1, 0));
    glm::vec3 model_scale = glm::vec3(0.1, 0.1, 0.1);

    float last = 0;
    float rot_vel = (float)(3.14 / 8);
    float angle = 0;

    window->keyboard.onPress.add([](GLwrap::KeyboardKey key, GLwrap::KeyMode mode){
        if (key == GLwrap::KeyboardKey::P){
            pause = !pause;
            std::cout << "Pressed" <<std::endl;
        }
    });


    while (running){
        float dt = timer->elapsed();
        last += dt;
        timer->start();

        float dist = cam_vel * dt;
        camMove(*window, *cam, dist);

        glClearColor(back_color.x, back_color.y, back_color.z, back_color.w);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        auto clear_time = timer->elapsed();

        dt = pause ? 0 : dt;
        #pragma omp parallel for num_threads(16)
        for (int i = 0; i < objects.size(); ++i){
            // objects[i]->time += dt;
            // objects[i]->transform.setR(glm::angleAxis((float)(angle), glm::vec3(0, 1, 0)));
            auto obj = objects[i];
            // obj->setAnimation(0);
            obj->setAnimationTime(obj->getAnimationTime() + dt);
            obj->update();
        }
        auto update_time = timer->elapsed() - clear_time;

        for (int i = 0; i < objects.size(); ++i){
            shader->draw(*objects[i]);
        }
        auto draw_time = timer->elapsed() - update_time;
        
        window->swapBuffers();
        glfwPollEvents();

        if (last > 1){
            // rot_vel = -rot_vel;

            std::cout << "================" << std::endl;
            std::cout << "Loop time: " << dt << std::endl;
            std::cout << "Clear time: " << clear_time << std::endl;
            std::cout << "Update time: " << update_time << std::endl;
            std::cout << "Draw time: " << draw_time << std::endl;
            std::cout << cam->pos[0] << "; " << cam->pos[1] << "; " << cam->pos[2] << std::endl;
            last = 0;
        }
    }

    return 0;
}
 