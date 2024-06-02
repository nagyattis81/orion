#version 330 core

uniform mat4 modelView = mat4(1.0);
uniform mat4 projection = mat4(1.0);

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aUV;

out vec2 uv;

void main()
{
    uv = aUV;
    gl_Position = projection * modelView * vec4(aPosition.x, aPosition.y, 0.0, 1.0);
}
