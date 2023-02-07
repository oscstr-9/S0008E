#include "config.h"
#include "Quad.h"

Quad::Quad(MathPlane plane, float size, VectorMath4 color){
    this->plane = plane;
    this->size = size;
    this->color = color;   
}

Quad::~Quad()
{
}

MathPlane Quad::GetPlane(){
    return this->plane;
}

float Quad::GetSize(){
    return this->size;
}

VectorMath4 Quad::GetColor(){
    return this->color;
}