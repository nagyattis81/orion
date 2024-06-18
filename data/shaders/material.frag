#version 330 core

out vec4 FragColor;

in vec3 vNormal;
in vec2 vTextureCoord;
in vec3 vVertex;

uniform float uAmbientIntensity = 1.0; // TODO from application

struct Material {
    vec3 ambient;
    vec3 diffuse;
    float opacity;
};
uniform Material uMaterial;

struct Texture {
    sampler2D ambient;
    sampler2D diffuse;
};
uniform Texture uTexture;

const vec3 uLightSource = vec3(1.0, 0.0, 0.0);  // TODO from application

vec3 Ambient() {
    return uMaterial.ambient * texture(uTexture.ambient, vTextureCoord).rgb * vec3(uAmbientIntensity);    
}

vec3 Diffuse() {
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightSource - vVertex);
    float diff = max(dot(norm, lightDir), 0.0);
    return uMaterial.diffuse * texture(uTexture.diffuse, vTextureCoord).rgb * diff;
}

void main() 
{
    vec3 result = Ambient() + Diffuse();
    FragColor = vec4(result, uMaterial.opacity);
}
