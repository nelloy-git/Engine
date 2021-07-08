#version 330 core

uniform mat4 model;

layout in vec3 vertPos;
layout in vec3 vertNorm;
layout in vec2 vertUV;
layout in vec4 vertTangent;

out vec2 fragUV;

void main(){
    gl_Position = model * vec4(vertPos, 1.0);
    fragUV = vec2(vertUV);
}