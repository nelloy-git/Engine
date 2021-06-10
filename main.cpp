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
 
#include "GLwrap/Window.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Program.h"

#include "Data/Model_glTF.h"

using namespace Graphics;
 
int main(int argc, const char** argv){
    int width = 640;
    int height = 480;

    auto window = std::make_unique<Window>(width, height, "Test");
    window->setActive(true);
    if (!window->setGlParam(WindowGLparam::DEPTH_TEST, true)){
        return 0;
    }

    Data::Model_glTF model3d;
    if (!model3d.load("../test/vikingroom/scene.gltf")){
        std::cout << "Can not open model." << std::endl;
        return 0;
    }

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
        return -1;
    }
 
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    bool running = true;
    while (running){
        window->onClose.add([&running](){
            running = false;
        });

        progr->use();
        auto model_loc = progr->getUniformLoc("model");
        auto view_loc = progr->getUniformLoc("view");
        auto proj_loc = progr->getUniformLoc("proj");
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        progr->setUniformMat4f("model", glm::value_ptr(model));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate<float>(view, glm::vec3(0.0f, 0.0f, -3.0f));
        progr->setUniformMat4f("view", glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective<float>(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1i(glGetUniformLocation(progr->id(), "texture0"), 0);
 
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        model3d.draw();

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
 
    // glfwTerminate();
    return 0;
}
 