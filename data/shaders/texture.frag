#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D text;
uniform vec4 color;

void main() 
{
    FragColor = texture(text, uv) * color;
}
