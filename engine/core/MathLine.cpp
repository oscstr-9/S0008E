#pragma once
#include "MathLine.h"
#include "MathPlane.h"

MathLine::MathLine(VectorMath3 start, VectorMath3 end)
{
    this->start = start;
    this->end = end;
}

MathLine::~MathLine()
{
    //hmm
}

VectorMath3 MathLine::Intersect(MathPlane plane){

}

VectorMath3 MathLine::GetStart(){
    return start;
}
VectorMath3 MathLine::GetEnd(){
    return end;
}