#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include <memory>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Context/Timer.h"
#include "Context/Window.h"

// #include "Graphics/Render/Base/Vertex.hpp"
// #include "Graphics/Model/Model.hpp"
// #include "Graphics/Render/Base/Primitive.hpp"-
#include "Graphics/Render/Base/Primitive.hpp"
#include "Graphics/Utils/Camera.hpp"

// #include "Graphics/Model/Loader/TinyGltf.hpp"

#include "Log.h"

using namespace Graphics;

const float cam_vel = 5;
const float cam_w = 3.14 / 2;
bool pause = false;

// auto *initRender(){
//     Render::VertexShaderGL vert;
//     Render::FragmentShaderGL frag;

//     return new Render::RendererGL(vert, frag);
// }

void camMove(glw::Window &window, Graphics::Draw::Camera &cam, float dist, float angle){
    if (pause){
        return;
    }
        
    if (window.keyboard.isDown(glw::KeyboardKey::W)){
        cam.pos += cam.direction * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::S)){
        cam.pos -= cam.direction * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::D)){
        cam.pos += cam.right * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::A)){
        cam.pos -= cam.right * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::SPACE)){
        cam.pos += cam.up * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::LEFT_CONTROL)){
        cam.pos -= cam.up * dist;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::LEFT)){
        cam.yaw -= angle;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::RIGHT)){
        cam.yaw += angle;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::UP)){
        cam.pitch -= angle;
    }

    if (window.keyboard.isDown(glw::KeyboardKey::DOWN)){
        cam.pitch += angle;
    }
}

// tinygltf::Model *loadMdlData(const std::string &path){
//     static tinygltf::TinyGLTF loader;
//     std::string err;
//     std::string warn;

//     auto gltf_model = new tinygltf::Model();

//     bool res = loader.LoadASCIIFromFile(gltf_model, &err, &warn, path);
//     if (!warn.empty()){
//         throw std::runtime_error(warn);
//     }

//     if (!err.empty()) {
//         throw std::runtime_error(err);
//     }

//     if (!res){
//         throw std::runtime_error("Failed to load glTF: " + path);
//     }

//     return gltf_model;
// }



int main(int argc, const char** argv){
    int width = 640;
    int height = 480;
    bool running = true;
    
    auto window = std::make_unique<glw::Window>(width, height, "Test");
    window->setActive(true);

    glEnable(GL_DEPTH_TEST);

    window->onClose.add([&running](){
        running = false;
    });


    std::vector<Render::Base::Vertex> vert;
    std::vector<unsigned int> index;

    // glw::ObjectIndexed(vert, index);
    Render::Base::Primitive prim(vert, index);
    




    auto cam = std::make_shared<Graphics::Draw::Camera>();
    cam->width = width;
    cam->height = height;
    cam->pos = glm::vec3(-0.3, 0, 0);

    auto timer = std::make_shared<glw::Timer>();
    timer->start();

    glm::vec4 back_color(0.2f, 0.3f, 0.3f, 1.0f);
    glm::vec3 model_translation(0.f);
    glm::quat model_rotation = glm::angleAxis((float)(3 * 3.1415 / 2), glm::vec3(0, 1, 0));
    glm::vec3 model_scale = glm::vec3(0.1, 0.1, 0.1);

    auto s = glm::scale(glm::mat4(1.f), model_scale);
    auto r = glm::mat4_cast(model_rotation);
    auto t = glm::translate(glm::mat4(1.f), model_translation);
    glm::mat4 mat = t * r * s;

    float last = 0;
    float rot_vel = (float)(3.14 / 8);
    // float angle = 0;

    window->keyboard.onPress.add([](glw::KeyboardKey key, glw::KeyMode mode){
        if (key == glw::KeyboardKey::P){
            pause = !pause;
            std::cout << "Pressed" <<std::endl;
        }
    });

    // Graphics::Render::Easy::Renderer renderer;
    // renderer.use();
    // Graphics::Model::Model mdl("../test/book/scene.gltf");
    // auto cube = Graphics::Render::Easy::Renderer::newCube();

    // auto model_data = loadMdlData("../test/book/scene.gltf");
    // auto model = Model::Loader::TinyGltf<Render::Easy::VERT_STRUCT>::newModel(*model_data);
    // delete model_data;

    while (running){
        float dt = timer->elapsed();
        last += dt;
        timer->start();

        float dist = cam_vel * dt;
        float angle = cam_w * dt;
        camMove(*window, *cam, dist, angle);

        glClearColor(back_color.x, back_color.y, back_color.z, back_color.w);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        auto clear_time = timer->elapsed();

        // for (auto &mesh : mdl.meshes){
        //     for (auto &prim : mesh->primitives){
        //         renderer.draw(*prim, cam->mat * mat, {});
        //     }
        // }
        // renderer.setCamera(cam->mat);
        // renderer.draw(*cube, mat, {});
        // renderer.draw(*model, mat, {});
        
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
 