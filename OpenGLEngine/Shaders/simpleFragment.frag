#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float uTime;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform mat4 transform;

void main()
{
    FragColor = mix(texture(tex, TexCoord), texture(tex2, TexCoord), 0.5);
}