#version 330 core
#extension GL_ARB_enhanced_layouts: enable

uniform mat4 model;


layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec2 TexCoord_0;
layout (location = 4) in vec2 TexCoord_1;
layout (location = 5) in vec3 Color_0;
layout (location = 6) in vec3 Joints_0;
layout (location = 7) in float Weights_0;

// Morph target
uniform int morph_targets;
uniform int morph_attributes;
uniform float morph_weights[8];
layout (location = 8) in vec3 MorphData[8];

out vec2 outTexCoord_0;
out vec2 outTexCoord_1;

void morph1Attrib(inout vec3 pos){
    for (int i = 0; i < min(morph_targets, 8); ++i){
        pos += morph_weights[i] * MorphData[i];
    }
}

void morph2Attrib(inout vec3 pos, inout vec3 norm){
    for (int i = 0; i < min(morph_targets, 4); ++i){
        pos += morph_weights[i] * MorphData[i];
        norm += morph_weights[i + 1] * MorphData[i + 1];
    }
}

void morph3Attrib(inout vec3 pos, inout vec3 norm, inout vec3 tang){
    for (int i = 0; i < min(morph_targets, 2); ++i){
        pos += morph_weights[i] * MorphData[i];
        norm += morph_weights[i + 1] * MorphData[i + 1];
        tang += morph_weights[i + 2] * MorphData[i + 2];
    }
}

void main(){
    vec3 morhed_position = Position;
    vec3 morhed_normal = Normal;
    vec3 morhed_tangent = Tangent;

    if (morph_attributes >= 3){
        morph3Attrib(morhed_position, morhed_normal, morhed_tangent);
    } else if (morph_attributes >= 2){
        morph2Attrib(morhed_position, morhed_normal);
    } else if (morph_attributes >= 1){
        morph1Attrib(morhed_position);
    }

    gl_Position = model * vec4(morhed_position, 1.0);

    outTexCoord_0 = vec2(TexCoord_0);
    outTexCoord_1 = vec2(TexCoord_1);
}