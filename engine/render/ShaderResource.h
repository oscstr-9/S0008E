#pragma once
#include <string>
#include "GL/glew.h"
#include "core/MatrixMath.h"
#include "core/VectorMath.h"
#include "render/Camera.h"

class ShaderResource
{
	GLuint program;
	MatrixMath renderPos;

public:
	ShaderResource();
	~ShaderResource();
	void LocationAndColor(MatrixMath locMat, VectorMath4 colorVec, ScreenCamera camera);
	GLuint LoadShader(std::string vertex_path, std::string fragment_path);
	void BindShader();
	void setVec3(VectorMath3 vec3, std::string uniform);
	void setVec4(VectorMath4 vec4, std::string uniform);
	void setMat4(MatrixMath mat4, std::string uniform);
	void setSampler(int index, std::string uniform);
	void setFloat(float floatIn, std::string uniform);
	void setLights(VectorMath3 lightColor[16], VectorMath3 lightPos[16], float intensity[16], int amountOfLights);
};
