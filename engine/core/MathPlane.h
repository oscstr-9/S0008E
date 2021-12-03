#pragma once
#include "VectorMath.h"

class MathPlane
{
private:
    VectorMath3 point = VectorMath3(0,0,0);
    VectorMath3 normal = VectorMath3(0,0,0);
public:
    MathPlane(class VectorMath3 point, class VectorMath3 normal);
    ~MathPlane();
    void QuadOnPlane();
    void GetPlaneParts(VectorMath3* point, VectorMath3* normal);
};
