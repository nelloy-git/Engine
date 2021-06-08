#version 330
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
   // FragColor = texture(ourTexture, TexCoord);
   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}