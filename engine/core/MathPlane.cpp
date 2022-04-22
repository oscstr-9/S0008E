#pragma once
#include "MathPlane.h"
#include "VectorMath.h"
#include "render/Vertex.h"
#include "render/RenderDebug.h"

MathPlane::MathPlane(VectorMath3 point, VectorMath3 normal)
{
    this->point = point;
    this->normal = normal;

}
MathPlane::~MathPlane()
{
}

void MathPlane::GetPlaneParts(VectorMath3 *pointIn, VectorMath3 *normalIn){
    *pointIn = this->point;
    *normalIn = this->normal;
}
