#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
 
#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "opencv/cv.hpp"
#include "opencv/highgui.h"
 
#include "Window.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Program.h"

#include "Data/Model.h"

using namespace Graphics;
 
std::string vertex_shader_text =
"#version 330\n"
"layout (location = 0) in vec3 vPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = view * model * vec4(vPos, 1.0);\n"
// "    gl_Position = vec4(vPos * 0.5, 1.0);\n"
"    TexCoord = aTexCoord;\n"
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

struct Vert {
    float x;
    float y;
    float z;
};

struct Triang {
    GLuint _1;
    GLuint _2;
    GLuint _3;
};

struct UV {
    float u;
    float v;
};

cv::Point2d calcNewPoint(cv::Mat distortion, double x, double y, double width, double height) {
    double k1 = distortion.at<double>(0);
    double k2 = distortion.at<double>(1);
    double p1 = distortion.at<double>(2);
    double p2 = distortion.at<double>(3);
    double k3 = distortion.at<double>(4);

    x -= width/2;
    y -= height/2;

    double r = sqrt(x * x + y * y);

    double x_n, y_n;
    x_n = x * (1 + k1 * r * r + k2 * pow(r, 4) + k3 * pow(r, 6)) + 2 * p1 * x * y +
          p2 * (r * r + 2 * x * x);
    y_n = y * (1 + k1 * r * r + k2 * pow(r, 4) + k3 * pow(r, 6)) + p1 * (r * r + 2 * y * y) +
          2 * p2 * x * y;

    x_n += width/2;
    y_n += height/2;

    // if (x_n >= width) {
    //     x_n = width;
    // } else if (x_n < 0) {
    //     x_n = 0;
    // }

    // if (y_n >= height) {
    //     y_n = height;
    // } else if (y_n < 0) {
    //     y_n = 0;
    // }

    return cv::Point2f(x_n, y_n);
}

static const double dist_data[] = {
    -3.5056089984425232e-01, 1.6842786388067377e-01, 0., 0., -4.8626959763779856e-02
};
static const cv::Mat dist_mat(1, 5, CV_32F, *dist_data);

std::vector<Vert> &getMesh(int width, int height){
    float step_x = 2 / (float)width;
    float step_y = 2 / (float)height;

    auto pRes = new std::vector<Vert>((width + 1) * (height + 1));
    auto& res = *pRes;

    for (int i = 0; i < width + 1; i++){
        for (int j = 0; j < height + 1; j++){
            float x = i * step_x - 1;
            float y = j * step_y - 1;

            res[i + j * (width + 1)] = {x, y, 0.f};
        }
    }
    return res;
}

std::vector<Triang> &getEnum(int width, int height){
    auto pRes = new std::vector<Triang>(2 * width * height);
    auto& res = *pRes;

    int p = 0;
    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; i++){
            int ind = i + j * (width + 1);

            GLuint _1 = ind;
            GLuint _2 = ind + 1;
            GLuint _3 = ind + (width + 1) + 1;
            GLuint _4 = ind + (width + 1);

            res[p++] = {_4, _1, _2};
            res[p++] = {_4, _2, _3};
        }
    }
    return res;
}

std::vector<UV> &getUVMap(int width, int height){
    float step_x = 1 / (float)width;
    float step_y = 1 / (float)height;

    auto pRes = new std::vector<UV>((width + 1) * (height + 1));
    auto& res = *pRes;

    for (int j = 0; j < height + 1; j++){
        for (int i = 0; i < width + 1; i++){
            auto p = calcNewPoint(dist_mat, i, j, (float)width, (float)height);
            res[i + j * (width + 1)] = {(float)p.x / (float)width, (float)p.y / (float)height};

            // double x = i * step_x;
            // double y = j * step_y;

            // res[i + j * (width + 1)] = {(float) x, (float) y};
        }
    }
    return res;
}

std::shared_ptr<Window> initGL(){
    auto window = std::make_shared<Window>(640, 480, "Test");
    window->setActive(true);
    
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(0);
    // glEnable(GL_DEPTH_TEST);

    return window;
}

std::shared_ptr<GLwrap::Program> initShader(){
    auto vshader = std::make_shared<GLwrap::Shader>(
        GLwrap::ShaderType::VERTEX, vertex_shader_text);

    auto fshader = std::make_shared<GLwrap::Shader>(
        GLwrap::ShaderType::FRAGMENT, fragment_shader_text);
 
    std::vector<std::shared_ptr<GLwrap::Shader>> shader_list;
    shader_list.push_back(vshader);
    shader_list.push_back(fshader);

    return std::make_shared<GLwrap::Program>(shader_list);
}

std::shared_ptr<GLwrap::VAO> initVAO(const std::vector<Vert> &vert,
                                     const std::vector<Triang> &triang,
                                     const std::vector<UV> &uv_map){
    auto vao = std::make_shared<GLwrap::VAO>();
    vao->bind();

    sizeof (std::vector<Triang>);
    sizeof (Triang);

    auto vertices = std::make_shared<GLwrap::VBO>(vert.size() * sizeof(Vert));
    vertices->load(&vert[0]);
    vertices->attrib(0, GLwrap::ShaderDataSize::Vec3, GLwrap::ShaderDataType::Float);

    auto uv = std::make_shared<GLwrap::VBO>(uv_map.size() * sizeof(UV));
    uv->load(&uv_map[0]);
    uv->attrib(1, GLwrap::ShaderDataSize::Vec2, GLwrap::ShaderDataType::Float);

    auto triangles = std::make_shared<GLwrap::EBO>(triang.size() * sizeof(Triang));
    triangles->load(&triang[0]);
    triangles->bind();

    vao->unbind();
    return vao;
}
 
int main(int argc, const char** argv){
    auto window = initGL();
    auto progr = initShader();


    int width = 640;
    int height = 480;
    float ratio = (float)width / (float)height;
    

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    // auto vert = getMesh(4, 3);
    // auto triang = getEnum(4, 3);
    // auto uv_map = getUVMap(4, 3);

    auto vert = getMesh(160, 120);
    auto triang = getEnum(160, 120);
    auto uv_map = getUVMap(160, 120);

    printf("Vertices: %d\n", (int)(vert.size()));

    int i = 0;
    for (auto pos : vert){
        printf("%d: [%.2f; %.2f; %.2f]\n", i, pos.x, pos.y, pos.z);
        i++;
    }

    i = 0;
    printf("UV: %d\n", (int)(uv_map.size()));
    for (auto v : uv_map){
        printf("%d: [%f; %f]\n", i, v.u, v.v);
        i++;
    }

    // i = 0;
    // printf("Enum: %d\n", (int)(triang.size()));
    // for (auto tr : triang){
    //     printf("%d: [%d; %d; %d]\n", i, tr._1, tr._2, tr._3);
    //     i++;
    // }

    auto cap = cv::VideoCapture("rtsp://root:123456@192.168.1.85/axis-media/media.amp");
    cv::Mat img;

    auto vao = initVAO(vert, triang, uv_map);

    bool running = true;
    while (running){
        window->onClose.add([&running](){
            running = false;
        });

        cap.read(img);

        auto start_draw_img = glfwGetTime();
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        // cv::imshow("CV", img);
        // cv::waitKey(1);

        glUseProgram(progr->id);
        glUniform1i(glGetUniformLocation(progr->id, "ourTexture"), 0); // set it manually
        
        glm::mat4 model = glm::mat4(1.0f);
        // model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
        // model = glm::translate(model, glm::vec3(-0.5, -0.5, 0));
        GLuint model_loc = glGetUniformLocation(progr->id, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate<float>(view, glm::vec3(0.0f, 0.0f, 0.f)); 
        GLuint view_loc = glGetUniformLocation(progr->id, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));


        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao->bind();
        glDrawElements(GL_TRIANGLES, 3 * triang.size(), GL_UNSIGNED_INT, 0);

        auto end_draw_img = glfwGetTime();

        // Measure speed
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            printf("%f ms to fraw\n", end_draw_img - start_draw_img);
            nbFrames = 0;
            lastTime += 1.0;
        }

        window->swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}