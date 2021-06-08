#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
#include "Window.h"
#include "GLwrap/Shader.h"
#include "GLwrap/Program.h"

#include "Data/Model.h"

using namespace Graphics;
 
std::string vertex_shader_text =
"#version 330\n"
"layout (location = 0) in vec3 vPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 1.0);\n"
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

cv::Point2f calcNewPoint(cv::Mat distortion, cv::Mat calib, float x, float y) {
    float k1 = distortion.at<float>(0);
    float k2 = distortion.at<float>(1);
    float p1 = distortion.at<float>(2);
    float p2 = distortion.at<float>(3);
    float k3 = distortion.at<float>(4);

    float vec_data[] = {x, y, 1};
    cv::Mat vec(3, 1, CV_32F, vec_data);

    cv::Mat norm = calib.inv() * vec;
    float z = norm.at<float>(2);

    // printf("(%.5f, %.5f, 1) * K^(-1) = (%.8f, %.8f, %.8f)\n", x, y, norm.at<float>(0), norm.at<float>(1), norm.at<float>(2));

    norm.at<float>(0) = norm.at<float>(0) / z;
    norm.at<float>(1) = norm.at<float>(1) / z;
    norm.at<float>(2) = norm.at<float>(2) / z;


    x = norm.at<float>(0);
    y = norm.at<float>(1);
    float r = sqrt(x * x + y * y);

    float x_n, y_n;
    x_n = x * (1 + k1 * r * r + k2 * pow(r, 4) + k3 * pow(r, 6)) + 2 * p1 * x * y +
          p2 * (r * r + 2 * x * x);
    y_n = y * (1 + k1 * r * r + k2 * pow(r, 4) + k3 * pow(r, 6)) + p1 * (r * r + 2 * y * y) +
          2 * p2 * x * y;

    float u = x_n * calib.at<float>(0, 0) + calib.at<float>(0, 2);
    float v = y_n * calib.at<float>(1, 1) + calib.at<float>(1, 2);

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

    return cv::Point2f(u, v);
}

static float dist_data[] = {
    -3.5056089984425232e-01, 1.6842786388067377e-01, 0., 0., -4.8626959763779856e-02
};
static const cv::Mat dist_mat(5, 1, CV_32F, dist_data);

static float calib_data[] = {
    1.0115571448254949e+03, 0., 9.8006255008915400e+02,
    0., 1.0088747715083081e+03, 5.5249589858831928e+02,
    0., 0., 1.    
};
static const cv::Mat calib_mat(3, 3, CV_32F, calib_data);

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
    static float im_w = 1920;
    static float im_h = 1080;

    float step_x = 1 / (float)width;
    float step_y = 1 / (float)height;

    auto pRes = new std::vector<UV>((width + 1) * (height + 1));
    auto& res = *pRes;

    for (int j = 0; j < height + 1; j++){
        for (int i = 0; i < width + 1; i++){
            float x = i * step_x;
            float y = j * step_y;

            auto p = calcNewPoint(dist_mat, calib_mat, x * im_w, y * im_h);
            res[i + j * (width + 1)] = {p.x / im_w, p.y / im_h};


            // res[i + j * (width + 1)] = {(float) x, (float) y};
        }
    }
    return res;
}

std::shared_ptr<Window> initGL(){
    auto window = std::make_shared<Window>(1920, 1080, "Test");
    window->setActive(true);
    
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(0);

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

    auto triangles = std::make_shared<GLwrap::VEO>(triang.size() * sizeof(Triang));
    triangles->load(&triang[0]);
    triangles->bind();

    vao->unbind();
    return vao;
}

void initProgr(){
    auto progr = initShader();
    glUseProgram(progr->id);
    glUniform1i(glGetUniformLocation(progr->id, "ourTexture"), 0); // set it manually
}

GLuint initTexture(){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}
 
int main(int argc, const char** argv){
    auto window = initGL();
    initProgr();

    int width = 1920;
    int height = 1080;
    float ratio = (float)width / (float)height;
    

    float lastTime = glfwGetTime();
    int nbFrames = 0;

    auto vert = getMesh(1920, 1080);
    auto triang = getEnum(1920, 1080);
    auto uv_map = getUVMap(1920, 1080);

    printf("Vertices: %d\n", (int)(vert.size()));
    printf("UV: %d\n", (int)(uv_map.size()));
    printf("Enum: %d\n", (int)(triang.size()));

    auto cap = cv::VideoCapture("rtsp://root:123456@192.168.1.85/axis-media/media.amp");
    cv::Mat img;

    auto vao = initVAO(vert, triang, uv_map);
    auto texture = initTexture();

    GLuint    query;                    // query id
    GLuint64 elapsedTime;              // затраченное время в наносекундах

    glGenQueries ( 1, &query );

    bool running = true;
    while (running){
        window->onClose.add([&running](){
            running = false;
        });

        cap.read(img);
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        glClear(GL_COLOR_BUFFER_BIT);

 
        // Начинаем запрос
        glBeginQuery ( GL_TIME_ELAPSED, query );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.cols, img.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        img.release();

        glViewport(0, 0, width, height);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        vao->bind();
        glDrawElements(GL_TRIANGLES, 3 * triang.size(), GL_UNSIGNED_INT, 0);
        glFinish();

        // Команды, время выполнения которых нас интересует
        glEndQuery ( GL_TIME_ELAPSED );

        glGetQueryObjectui64v ( query, GL_QUERY_RESULT, &elapsedTime );

        // Measure speed
        float currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer

            printf("%f ms/frame\n", 1000.0/float(nbFrames));
            printf("%.3f ms to draw\n", (float)elapsedTime / 1000000000);
            nbFrames = 0;
            lastTime += 1.0;
        }

        window->swapBuffers();
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glfwTerminate();
    return 0;
}