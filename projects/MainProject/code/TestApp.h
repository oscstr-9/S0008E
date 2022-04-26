#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "core/MathLine.h"
#include "core/MathPlane.h"
#include "render/ShaderResource.h"
#include "render/window.h"
#include "render/Lighting.h"
#include "render/GraphicsNode.h"
#include "render/MeshResource.h"
#include "render/TextureResource.h"
#include "render/gltfLoader.h"

#include <memory>
#include <vector>

namespace Example
{
class ExampleApp : public Core::App
{
public:
	// constructor
	ExampleApp();
	// destructor
	~ExampleApp();

	// Bind multiple lights at once
	void bindLights(std::vector<Lighting> lights);

	// open app
	bool Open();

	// run app
	void Run();

	void MoveCamera(VectorMath3 &cameraPos);
private:
	// Display screen
	Display::Window* window;
	int width, height;

	// Camera movement
	bool up = false;
	bool down = false;
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
	float speed = 0.01;
	float mvmtSpeed = 0.1;

	// Rendering
	std::shared_ptr<ShaderResource> shaders;
	std::vector<gltfInfo> gltfMesh;
	GraphicsNode gltfModel;

	ScreenCamera camera;
	// Transforms
	VectorMath3 cameraPos = VectorMath3(0, 5, 5);
	VectorMath3 cameraRotation = VectorMath3(0,0,0);

	MatrixMath posMat = Identity();
	MatrixMath rotMat = Identity();

	std::vector<MathLine> mathLines;

	// Debugging
	bool debug = true;
};
}
