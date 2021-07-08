#version 330 core

uniform mat4 model;

in vec3 Position;
in vec3 Normal;
in vec3 Tangent;
in vec2 TexCoord_0;

out vec2 fragUV;

void main(){
    gl_Position = model * vec4(Position, 1.0);
    fragUV = vec2(TexCoord_0);
}