#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNorm;
layout (location = 2) in vec3 inUV;

out vec2 fragUV;

void main(){
    gl_Position = proj * view * model * vec4(inPos, 1.0);
    fragUV = inUV.xy
}