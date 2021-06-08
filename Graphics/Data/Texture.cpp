#include "Data/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Graphics::Data;

Texture::Texture(const std::string &path) : 
    path(path),
    data(stbi_load(path.c_str(),
            const_cast<int*>(&width),
            const_cast<int*>(&height),
            const_cast<int*>(&channels),
            STBI_rgb_alpha), stbi_image_free){
}
