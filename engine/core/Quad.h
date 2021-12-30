#pragma once
#include "core/VectorMath.h"
#include "core/MathPlane.h"

class Quad
{
private:
    MathPlane plane = MathPlane(VectorMath3(0,0,0), VectorMath3(1,0,0));
    float size;
    VectorMath4 color;
public:
    Quad(MathPlane plane, float size, VectorMath4 color);
    ~Quad();
    MathPlane GetPlane();
    float GetSize();
    VectorMath4 GetColor();
};