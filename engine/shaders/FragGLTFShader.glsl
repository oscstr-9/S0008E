#version 430

layout(location=0) in vec4 Colors;
layout(location=1) in vec2 texturesOut;
layout(location=2) in vec3 fragPos;
layout(location=3) in vec3 normalOut;
layout(location=4) in vec4 tangentsOut;

uniform sampler2D textureArray;
uniform sampler2D normalArray;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float intensity;
uniform vec3 viewPos;
uniform float specIntensity;
uniform vec4 colorInput;
out vec4 Color;

void main()
{	
	vec3 bitangent = cross(normalOut, tangentsOut.xyz)*tangentsOut.w;
	mat3 tbn = mat3(tangentsOut.xyz, normalOut, bitangent);
	vec3 normal = tbn * texture(normalArray, texturesOut).xyz;

	vec3 viewDir = normalize(fragPos - viewPos);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	vec3 ambient = intensity * lightColor;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float spec = pow(max(dot(normal, halfwayDir), 0.0), 64);
	vec3 specular = lightColor * spec;

	Color = texture(textureArray, texturesOut)  * vec4(ambient + diffuse + specular, 1.0) * colorInput;
};
