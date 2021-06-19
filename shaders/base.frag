#version 330

in vec2 fragUV;

uniform vec4 baseColor;

uniform sampler2D texture0;

void main()
{
   gl_FragColor = texture(texture0, fragUV) * baseColor;
   // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}