#version 330 core
#extension GL_ARB_enhanced_layouts: enable

uniform mat4 model;

uniform float morph_weights[4];
uniform int morph_weights_used;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3, component = 0) in vec2 TexCoord_0;
layout (location = 3, component = 2) in vec2 TexCoord_1;
layout (location = 5) in vec3 Color_0;
layout (location = 6) in vec3 Joints_0;
layout (location = 7) in vec3 Joints_1;
layout (location = 8) in float Weights_0;
layout (location = 9) in float Weights_1;

// Morph target

layout (location = 10) in vec3 Target0_Position;
layout (location = 11) in vec2 Target0_Normal;
layout (location = 12) in vec2 Target0_Tangent;
layout (location = 13) in vec3 Target1_Position;
layout (location = 14) in vec2 Target1_Normal;
layout (location = 15) in vec2 Target1_Tangent;
layout (location = 16) in vec3 Target2_Position;
layout (location = 17) in vec2 Target2_Normal;
layout (location = 18) in vec2 Target2_Tangent;
layout (location = 19) in vec3 Target3_Position;
layout (location = 20) in vec2 Target3_Normal;
layout (location = 21) in vec2 Target3_Tangent;

out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

void main(){
    vec3 morhed_position = Position;
    if (morph_weights_used > 0){
        morhed_position = morhed_position + morph_weights[0] * Target0_Position;
    }

    if (morph_weights_used > 1){
        morhed_position = morhed_position + morph_weights[1] * Target1_Position;
    }

    // if (morph_weights_used > 2){
    //     morhed_position = morhed_position + morph_weights[2] * Target2_Position;
    // }

    // if (morph_weights_used > 3){
    //     morhed_position = morhed_position + morph_weights[3] * Target1_Position;
    // }

    gl_Position = model * vec4(morhed_position, 1.0);

    outTexCoord_0 = vec2(TexCoord_0);
    outTexCoord_1 = vec2(TexCoord_1);
}