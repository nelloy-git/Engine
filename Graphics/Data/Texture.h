#pragma once

#include <memory>
#include <string>

namespace Graphics::Data {

class Texture {
public:
    Texture(const std::string &path);
    ~Texture(){};

    const std::string path;
    const int width = 0;
    const int height = 0;
    const int channels = 0;
    const std::shared_ptr<unsigned char[]> data;

};

}