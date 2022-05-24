#version 430

layout(location=0) in vec4 Color;
layout(location=1) in vec3 Normal;
layout(location=2) in vec3 WorldPos;
layout(location=3) in vec3 Specular;

out vec3 colorOut;

void main(){



    colorOut = color + Normal + fragPos;
}