#include "Data/Material.h"

#include <stdexcept>

#include "Log.h"

#include "GLwrap/Program.h"

using namespace Graphics; 

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
        base_texture->setActive(base_texture_uv);
    }
}