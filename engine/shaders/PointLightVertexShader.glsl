#version 430

layout(location=0) in vec3 pos;

uniform mat4 projectionViewMatrix;
uniform mat4 posMatrix;

void main(){
	gl_Position = projectionViewMatrix*posMatrix*vec4(pos, 1);
}