#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
// #include "render/MESHRESOURCE.h"
// #include "render/GraphicsNode.h"
#include "render/ShaderResource.h"
#include "render/window.h"
#include <memory>

#include "Player.h"
#include "Enemy.h"
#include "Tilegrid.h"
#include "CollisionHandler.h"

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();
	/// open app
	bool Open();
	void ControllerInputs();
	void spawnPlayerObject(int id, int tileX, int tileY);
	void spawnEnemyObject(int id, int tileX, int tileY);
	Pos tileToWorldPos(Pos tilePos);
	/// run app
	void Run();
private:
	//screen size
	int width, height;

	bool quit = false;
	float size = 1;
	float speed = 0.003;
	int spawnID = 1;

	MatrixMath camRotMat = MatrixMath::TranslationMatrix(VectorMath3(0, 3, -2)) * RotateMatrix(M_PI/5, VectorMath3(-1, 0, 0));
	MatrixMath posMat = Identity();
	MatrixMath characterPosMat = Identity();
	VectorMath3 cameraPos = VectorMath3(0, 3, 0);
	std::shared_ptr<ShaderResource> shaders;
	// GraphicsNode* objObject;
	Display::Window* window;

	Player player;
	Enemy enemy;


	Tilegrid* tilegrid;
	CollisionHandler* collisionHandler;
	std::vector<GameObject*> gameObjects;
};
} // namespace Example