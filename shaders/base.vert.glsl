#version 330 core

uniform mat4 model;

layout (location = 0) in vec4 data_0;
layout (location = 1) in vec4 data_1;
layout (location = 2) in vec4 data_2;
layout (location = 3) in vec4 data_3;
layout (location = 4) in vec4 data_4;
layout (location = 5) in vec4 data_5;
layout (location = 6) in vec4 data_6;
layout (location = 7) in vec4 data_7;
layout (location = 8) in vec4 data_8;
layout (location = 9) in vec4 data_9;
layout (location = 10) in vec4 data_10;
layout (location = 11) in vec4 data_11;
layout (location = 12) in vec4 data_12;
layout (location = 13) in vec4 data_13;
layout (location = 14) in vec4 data_14;
layout (location = 15) in vec4 data_15;

out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

vec3 getPos(){
    return data_0.xyz;
}

vec3 getNorm(){
    return vec3(data_0.w, data_1.xy);
}

vec3 getTang(){
    return vec3(data_1.zw, data_2.x);
}

vec3 getColor(){
    return data_2.yzw;
}

vec2 getTexCoord_0(){
    return data_3.xy;
}

vec2 getTexCoord_1(){
    return data_3.zw;
}

vec4 getJoints_0(){
    return data_4;
}

vec4 getJoints_1(){
    return data_5;
}

vec4 getWeights_0(){
    return data_6;
}

vec4 getWeights_1(){
    return data_7;
}

vec3 getMorph_0(){
    return data_8.xyz;
}

vec3 getMorph_1(){
    return vec3(data_8.w, data_9.xy);
}

vec3 getMorph_2(){
    return vec3(data_9.zw, data_10.x);
}

vec3 getMorph_3(){
    return data_10.yzw;
}

vec3 getMorph_4(){
    return data_11.xyz;
}

vec3 getMorph_5(){
    return vec3(data_11.w, data_12.xy);
}

vec3 getMorph_6(){
    return vec3(data_12.zw, data_13.x);
}

vec3 getMorph_7(){
    return data_13.yzw;
}

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