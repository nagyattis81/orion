#version 330 core

uniform mat4 uMVP = mat4(1.0);
uniform mat3 uNormalMatrix = mat3(1.0);
uniform mat4 uModelViewMatrix = mat4(1.0);

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

out vec3 vNormal;
out vec2 vTextureCoord;
out vec3 vVertex;

void main()
{
    vNormal = normalize(uNormalMatrix * aNormal);
    vTextureCoord = aTextureCoord;
    vVertex = vec3(uModelViewMatrix * vec4(aPosition, 1.0));
    gl_Position = uMVP * vec4(aPosition, 1.0);
}
