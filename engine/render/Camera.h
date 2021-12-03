#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"

class ScreenCamera
{
private:
	VectorMath3 pos;
	MatrixMath rotMat = Identity();
	MatrixMath projectionMat;

public:
	ScreenCamera();
	ScreenCamera(float FOV, int width, int height, float near, float far);
	~ScreenCamera();
	void Setup(float FOV, int width, int height, float near, float far);
	void SetRotation(VectorMath3 axisIn, float radIn );
	void SetPosition(VectorMath3 posIn);
	void SetRotMat(MatrixMath rotMatIn);
	MatrixMath GetProjViewMatrix();
	MatrixMath GetViewMatrix();
	MatrixMath GetRotMat();
	VectorMath3 GetPosition();
	VectorMath3 GetVectorX();
	VectorMath3 GetVectorY();
	VectorMath3 GetVectorZ();
};