#version 430

layout(location=0) in vec3 pos;

layout(location=0) out vec3 fragPos;

uniform mat4 projectionViewMatrix;
uniform mat4 posMatrix;

void main(){
	gl_Position = projectionViewMatrix*posMatrix*vec4(pos, 1);
	fragPos = (posMatrix*vec4(pos,1)).xyz;
}