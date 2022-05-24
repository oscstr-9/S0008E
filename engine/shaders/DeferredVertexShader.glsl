#version 430

layout(location=0) in vec4 color;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 worldPos;
layout(location=3) out vec3 specular;

layout(location=0) out vec4 Color;
layout(location=1) out vec3 Normal;
layout(location=2) out vec3 WorldPos;
layout(location=3) out vec3 Specular;

void main(){
 Color = color;
 Normal = normal;
 WorldPos = worldPos;
 Specular.rgb = texture(texture_diffuse1, texturesOut)specular;
}