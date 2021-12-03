#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "core/MathLine.h"
#include "render/Vertex.h"

namespace Debug{
void Render(MatrixMath projView);
void CreateGrid(int size, VectorMath4 color);
void DrawSquare(float size, VectorMath3 pos, VectorMath4 color);
void DrawLine(VectorMath3 start, VectorMath3 end, VectorMath4 color);
void DrawLine(MathLine line, VectorMath4 color);
}