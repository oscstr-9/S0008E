#pragma once
#include "VectorMath.h"

class MathLine
{
private:
    VectorMath3 start = VectorMath3(0,0,0);
    VectorMath3 end = VectorMath3(0,0,0);
public:
    MathLine(VectorMath3 start, VectorMath3 end);
    ~MathLine();
    VectorMath3 Intersect(class MathPlane plane);
    VectorMath3 GetStart();
    VectorMath3 GetEnd();
};