#include "Draw/Material.h"

#include <stdexcept>

#include "Log.h"

#include "GLwrap/Program.h"

using namespace Graphics::Draw; 

Material::Material(){
}

Material::~Material(){
}

void Material::apply(){
    auto progr = GLwrap::Program::getActive();
    if (progr == nullptr){
        return;
    }

    progr->setUniformVec4f("baseColor", base_color);
    if (base_texture){
        base_texture->enable(base_texture_uv);
    }
}