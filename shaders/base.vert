#version 330 core

uniform mat4 model;

layout (location=0) in vec3 Position;
layout (location=1) in vec3 Normal;
layout (location=2) in vec3 Tangent;
layout (location=3) in vec2 TexCoord_0;

out vec2 fragUV;

void main(){
    gl_Position = model * vec4(Position, 1.0);
    fragUV = vec2(TexCoord_0);
}