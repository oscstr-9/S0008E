#include "RenderDebug.h"
#include "render/ShaderResource.h"
#include <GL/glew.h>

#define MAX_SIZE 8192*4

namespace Debug{
    struct Vertex{
        VectorMath3 pos;
	    VectorMath4 color;
    };
    struct debugRenderBuffer{
        unsigned int vbo = 0;
        unsigned int numOfVert = 0;
        Vertex vertex[MAX_SIZE];
        ShaderResource shader;
    };

debugRenderBuffer squareBuffer;
debugRenderBuffer lineBuffer;
inline void PushVertex(debugRenderBuffer *buf, Vertex vertex){
    if (buf->numOfVert >= MAX_SIZE)
        return;

    else{
        buf->vertex[buf->numOfVert] = vertex;
        buf->numOfVert ++;
    }
}
void Render(MatrixMath projView){
    // For squares
    if(squareBuffer.vbo <= 0){
        glGenBuffers(1, &squareBuffer.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, squareBuffer.vbo);

        glBufferData(GL_ARRAY_BUFFER, MAX_SIZE*sizeof(Vertex), 0, GL_DYNAMIC_DRAW);

        squareBuffer.shader.LoadShader("DebugVertexShader.glsl","DebugFragShader.glsl");
    }
    else{
        glBindBuffer(GL_ARRAY_BUFFER, squareBuffer.vbo);
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, squareBuffer.numOfVert*sizeof(Vertex), squareBuffer.vertex);
    squareBuffer.shader.setMat4(projView, "projectionViewMatrix");
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(VectorMath3));

    glDrawArrays(GL_TRIANGLES, 0, squareBuffer.numOfVert);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    squareBuffer.numOfVert = 0;

//-------------------------------------------//
    // For lines
    if(lineBuffer.vbo <= 0){
    glGenBuffers(1, &lineBuffer.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, lineBuffer.vbo);

    glBufferData(GL_ARRAY_BUFFER, MAX_SIZE*sizeof(Vertex), 0, GL_DYNAMIC_DRAW);

    lineBuffer.shader.LoadShader("DebugVertexShader.glsl","DebugFragShader.glsl");
    }
    else{
        glBindBuffer(GL_ARRAY_BUFFER, lineBuffer.vbo);
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, lineBuffer.numOfVert*sizeof(Vertex), lineBuffer.vertex);
    lineBuffer.shader.setMat4(projView, "projectionViewMatrix");
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(VectorMath3));

    glDrawArrays(GL_LINES, 0, lineBuffer.numOfVert);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    lineBuffer.numOfVert = 0;
}

void CreateGrid(int size, VectorMath4 color){
    DrawLine(VectorMath3(-size, 0, -size), VectorMath3(size, 0,-size), color);
    DrawLine(VectorMath3(-size, 0, -size), VectorMath3(-size, 0, size), color);

    for (int i = 0; i < size; i++)
    {
        DrawLine(VectorMath3(size, 0, size-i*2), VectorMath3(-size, 0, size-i*2), color);
        DrawLine(VectorMath3(size-i*2, 0, size), VectorMath3(size-i*2, 0, -size), color);
    } 
}

// Create a square with set size and color
void DrawSquare(float size, VectorMath3 pos, VectorMath4 color){
    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(-0.5*size, -0.5 * size, 0), color});
    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(0.5*size, -0.5 * size, 0), color});
    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(0.5*size, 0.5 * size, 0), color});

    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(-0.5*size, -0.5 * size, 0), color});
    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(-0.5*size, 0.5 * size, 0), color});
    PushVertex(&squareBuffer, Vertex{pos + VectorMath3(0.5*size, 0.5 * size, 0), color});
}

// Create a line with start and end positions
void DrawLine(VectorMath3 start, VectorMath3 end, VectorMath4 color){
    PushVertex(&lineBuffer, Vertex{start, color});
    PushVertex(&lineBuffer, Vertex{end, color});
}
// Create a line with math line and color
void DrawLine(MathLine line, VectorMath4 color){
    PushVertex(&lineBuffer, Vertex{line.GetStart(), VectorMath4(1,0,0,1)});
    PushVertex(&lineBuffer, Vertex{line.GetEnd(), VectorMath4(0,1,0,1)});
}
}