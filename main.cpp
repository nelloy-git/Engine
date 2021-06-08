#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
 
#include <stdlib.h>
#include <stdio.h>
#include <memory>
 
#include "Window.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Program.h"

#include "Data/Model.h"

using namespace Graphics;
 
std::string vertex_shader_text =
"#version 330\n"
"layout (location = 0) in vec3 vPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(vPos, 1.0);\n"
"}\n";
 
std::string fragment_shader_text =
"#version 330\n"   
"out vec4 FragColor;"
""
"in vec2 TexCoord;\n"
""
"uniform sampler2D ourTexture;\n"
""
"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord);"
// "    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";
 
int main(int argc, const char** argv){
    
    auto window = new Window(640, 480, "Test");
    window->setActive(true);
    
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);

    Data::Model model3d;
    if (!model3d.load("../test/OBJ/rifle.obj")){
        return 0;
    }


    auto vshader = std::make_shared<GLwrap::Shader>(
        GLwrap::ShaderType::VERTEX, vertex_shader_text);

    auto fshader = std::make_shared<GLwrap::Shader>(
        GLwrap::ShaderType::FRAGMENT, fragment_shader_text);
 
    std::vector<std::shared_ptr<GLwrap::Shader>> shader_list;
    shader_list.push_back(vshader);
    shader_list.push_back(fshader);

    auto progr = std::make_shared<GLwrap::Program>(shader_list);


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
        glUseProgram(progr->id);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        GLuint model_loc = glGetUniformLocation(progr->id, "model");
        if ((int)model_loc < 0){
            printf("model_loc: %d\n", model_loc);
            continue;
        }
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate<float>(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        GLuint view_loc = glGetUniformLocation(progr->id, "view");
        if ((int)view_loc < 0){
            printf("view_loc: %d\n", view_loc);
            continue;
        }
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective<float>(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        GLuint projection_loc = glGetUniformLocation(progr->id, "projection");
        if ((int)projection_loc < 0){
            printf("projection_loc: %d\n", projection_loc);
            continue;
        }
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans, (float)glfwGetTime() * glm::pi<float>() / 4, glm::vec3(0.0, 0.0, 1.0));
        // trans = glm::scale(trans, glm::vec3(0.01, 0.01, 0.01));  
 
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            

        for (auto mesh : model3d.meshes()){

            mesh->draw();
            // glDrawArrays(GL_TRIANGLES, 0, mesh->count_vertices());
        }
        

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
 