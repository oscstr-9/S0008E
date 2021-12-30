#pragma once
#include "VectorMath.h"

class MathPlane
{
private:
    VectorMath3 point = VectorMath3(0,0,0);
    VectorMath3 normal = VectorMath3(0,0,0);
public:
    MathPlane(VectorMath3 point, VectorMath3 normal);
    ~MathPlane();
    void GetPlaneParts(VectorMath3 &point, VectorMath3 &normal);
};
