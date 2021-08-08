#version 330

in vec2 outTexCoord_0;
in vec2 outTexCoord_1;

uniform vec4 baseColor;
uniform int morph_targets;
uniform int morph_attributes;
uniform float morph_weights[8];

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
   if (morph_targets > 0){
      gl_FragColor = vec4(float(morph_attributes) / 10, 0, 0, 0);
   } else {
      gl_FragColor = texture(texture0, outTexCoord_0) * texture(texture1, outTexCoord_1) * baseColor;
   }
   // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}