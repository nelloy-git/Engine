#version 330

in vec2 fragUV;

uniform sampler2D texture0;

void main()
{
   gl_FragColor = texture(texture0, fragUV);
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}