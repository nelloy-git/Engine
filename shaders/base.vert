#version 330 core

uniform mat4 model;

layout (location = 0) in vec3 vertModelPos;
layout (location = 1) in vec3 vertNorm;
layout (location = 2) in vec2 vertUV;
layout (location = 3) in vec4 vertTangent;

out vec2 fragUV;

void main(){
    gl_Position = model * vec4(vertPos, 1.0);
    fragUV = vec2(vertUV);
}