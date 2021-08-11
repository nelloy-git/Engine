R"(
#version 420 core

uniform mat4 primitive_mat;

out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

void main(){
    vec3 morhed_position = getPos();
    vec3 morhed_normal = getNorm();
    vec3 morhed_tangent = getTang();

    // if (morph_attributes >= 3){
    //     morph3Attrib(morhed_position, morhed_normal, morhed_tangent);
    // } else if (morph_attributes >= 2){
    //     morph2Attrib(morhed_position, morhed_normal);
    // } else if (morph_attributes >= 1){
    //     morph1Attrib(morhed_position);
    // }

    gl_Position = model * vec4(morhed_position, 1.0);

    outTexCoord_0 = getTexCoord_0();
    outTexCoord_1 = getTexCoord_1();
}
)"