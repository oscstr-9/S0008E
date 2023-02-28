#version 430

layout(location=0) in vec4 Colors;
layout(location=1) in vec2 texturesOut;
layout(location=2) in vec3 fragPos; // in world space
layout(location=3) in vec3 normalOut;
layout(location=4) in vec4 tangentsOut;

uniform sampler2D textureArray;
uniform sampler2D normalArray;
uniform vec4 colorInput;

layout(location=0) out vec3 color;
layout(location=1) out vec3 normal;
layout(location=2) out vec3 worldPos;
layout(location=3) out vec3 specular;


void main()
{	
	vec3 bitangent = cross(normalOut, tangentsOut.xyz)*tangentsOut.w;
	mat3 tbn = mat3(tangentsOut.xyz, bitangent, normalOut);
	normal = tbn * normalize((texture(normalArray, texturesOut).xyz * 2 -1));

	worldPos = fragPos;

	color = (texture(textureArray, texturesOut) * colorInput).xyz;
};
