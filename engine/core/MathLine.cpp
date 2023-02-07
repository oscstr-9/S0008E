#pragma once
#include "config.h"
#include "MathLine.h"


MathLine::MathLine(VectorMath3 start, VectorMath3 end)
{
    this->start = start;
    this->end = end;
}

MathLine::~MathLine()
{
    //hmm
}

VectorMath3 MathLine::Intersect(std::vector<MathPlane> &planes){
    for (int i = 0; i < planes.size(); i++)
    {
        VectorMath3 point, normal;
        planes[i].GetPlaneParts(&point, &normal);
    }
    return VectorMath3{ 0,0,0 };
}

VectorMath3 MathLine::GetStart(){
    return start;
}
VectorMath3 MathLine::GetEnd(){
    return end;
}