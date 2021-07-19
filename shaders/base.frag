#version 330

in vec2 outTexCoord_0;
in vec2 outTexCoord_1;

uniform vec4 baseColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
   gl_FragColor = texture(texture0, outTexCoord_0) * texture(texture1, outTexCoord_1) * baseColor;
   // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}