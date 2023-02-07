#version 430

layout(location=0) in vec3 pos;
layout(location=1) in vec4 color;
layout(location=2) in vec2 texturesIn;
layout(location=3) in vec3 normalIn;
layout(location=4) in vec4 tangentsIn;

layout(location=0) out vec4 Colors;
layout(location=1) out vec2 texturesOut;
layout(location=2) out vec3 fragPos;
layout(location=3) out vec3 normalOut;
layout(location=4) out vec4 tangentsOut;

uniform mat4 posMatrix;
uniform mat4 projectionViewMatrix;
uniform vec4 colorVector;
uniform sampler2D textureArray;

void main()
{
	gl_Position = projectionViewMatrix*posMatrix*vec4(pos, 1);
	Colors = colorVector*color;
	texturesOut = texturesIn;
	tangentsOut = vec4(mat3(transpose(inverse(posMatrix))) * tangentsIn.xyz, tangentsIn.w);

	fragPos = (posMatrix*vec4(pos,1)).xyz;
	normalOut = mat3(transpose(inverse(posMatrix))) * normalIn;
};
