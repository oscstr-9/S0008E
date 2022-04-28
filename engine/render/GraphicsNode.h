#pragma once

#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include "gltfLoader.h"
#include <memory>

class GraphicsNode
{

	std::shared_ptr <MeshResource> mesh;
    std::shared_ptr <TextureResource> texture;
    std::shared_ptr <ShaderResource> shader;
    MatrixMath transform;

    std::vector<gltfInfo> model;

    bool isGltf = false;

public:
    GraphicsNode();
	GraphicsNode(std::shared_ptr <MeshResource> meshIn, std::shared_ptr <TextureResource> textureIn, std::shared_ptr <ShaderResource> shaderIn, MatrixMath transformIn);
	GraphicsNode(std::vector<gltfInfo> model, std::string fileName, std::shared_ptr <ShaderResource> shaderIn, MatrixMath transformIn);
	~GraphicsNode();

    void Draw();
    void DrawOBJ();
    void DrawGLTF();
 
    std::shared_ptr<MeshResource> getMesh() const;
    void setMesh(std::shared_ptr<MeshResource> mesh);

    std::shared_ptr<TextureResource> getTexture() const;
    void setTexture(std::shared_ptr<TextureResource> texture);

    std::shared_ptr<ShaderResource> getShader() const;
    void setShader(std::shared_ptr<ShaderResource> shader);

    MatrixMath getTransform() const;
    void setTransform(MatrixMath transform);

};