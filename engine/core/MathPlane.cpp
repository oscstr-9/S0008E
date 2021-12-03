#pragma once
#include "MathPlane.h"
#include "VectorMath.h"

MathPlane::MathPlane(VectorMath3 point, VectorMath3 normal)
{
    this->point = point;
    this->normal = normal;
}
MathPlane::~MathPlane()
{
}

void MathPlane::QuadOnPlane(){
    
}
void MathPlane::GetPlaneParts(VectorMath3* point, VectorMath3* normal){
    point = &this->point;
    normal = &this->normal;
}
