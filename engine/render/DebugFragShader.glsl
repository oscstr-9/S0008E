#version 300 es
#extension GL_EXT_separate_shader_objects : require
precision highp float;

layout(location=0) in vec4 Colors;
layout(location=1) in vec2 texturesOut;

out vec4 Color;

void main()
{	
	Color =  Colors;
};
