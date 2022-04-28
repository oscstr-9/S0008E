#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "render/ShaderResource.h"


struct gltfInfo{
    GLuint vertBuffer;
    GLuint indexBuffer;
    GLuint texture;
    GLuint normalMap;
    VectorMath4 color;
    int componentType;
    int posByteStride;
    int posByteLength;
    int texByteStride;
    int texByteLength;
    int normalByteStride;
    int normalByteLength;
    int indexCount;
    int tangentByteStride;
    int tangentByteLength;
};

void LoadGLTF(std::string fileName, std::vector<gltfInfo>& info);
void RenderGLTF(std::vector<gltfInfo>& info,  std::shared_ptr <ShaderResource> shader);