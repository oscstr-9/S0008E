//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
//#include <stb_image.h>
#include <cstring>
#include "config.h"
#include "TestApp.h"
#include "core/MatrixMath.h"
#include "render/Camera.h"
#include "render/RenderDebug.h"

using namespace Display;
namespace Example
{
	ExampleApp::ExampleApp()
	{/*cool*/}
	ExampleApp::~ExampleApp()
	{/*so cool*/}

	void ExampleApp::ShootFromMousePos(){
		double x = 0, y = 0;
		glfwGetCursorPos(window->window, &x, &y);

		x /= width;
		y /= height;
		x = (x*2)-1;
		y = (y*2)-1;
		y*=-1;
		VectorMath4 p = VectorMath4(x,y,1,1);
		MatrixMath invVPMatrix = camera.GetProjViewMatrix().InverseMatrix();
		p = invVPMatrix.VectorMultiplication(VectorMath4(p,1));
		VectorMath4 cameraWorldPos = camera.GetViewMatrix().InverseMatrix().VectorMultiplication(VectorMath4(0,0,0,1));
		cameraWorldPos.w = 1;
		p = p + cameraWorldPos;
		//VectorMath4 forwardVector = (camera.GetProjViewMatrix() * camera.GetRotMat().InverseMatrix()).VectorMultiplication(VectorMath4(camera.GetVectorZ(),1));
		//mouseWorldPos = mouseWorldPos + VectorMath4(cameraPos,1);

		VectorMath4 direction = p - cameraWorldPos;
		cameraWorldPos.PrintVector();
		mathLines.push_back(MathLine(cameraPos, cameraPos + VectorMath3(direction)*100));
	}

	bool ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		// Adding mouse functionality			
		window->SetMousePressFunction([this](int32 button, int32 action, int32 mods){
			if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
				ShootFromMousePos();
			}
			if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
				mathLines.clear();
			}
		});
		window->SetKeyPressFunction([this](int32 keycode, int32, int32 action, int32)
			{
			// Adding keyboard functionality
			switch (keycode)
			{
			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				forward = action;
				break;
			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				backward = action;
				break;
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				left = action;
				break;
			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				right = action;
				break;
			case GLFW_KEY_SPACE:
				up = action;
				break;
			case GLFW_KEY_LEFT_SHIFT:
				down = action;
				break;
			case GLFW_KEY_F1:
				if(action == GLFW_PRESS){
					debug = !debug;
				}
				break;
			case GLFW_KEY_ESCAPE:
				this->window->Close();
				break;
			case GLFW_KEY_TAB:
				if(action == GLFW_PRESS && mvmtSpeed < 3){
					mvmtSpeed += 0.5;
				}
				break;
			case GLFW_KEY_LEFT_CONTROL:
				if(action == GLFW_PRESS  && mvmtSpeed > 0.5){
					mvmtSpeed -= 0.5;
				}
				break;
			case GLFW_KEY_LEFT_ALT:
				if(action == GLFW_PRESS)
					freeMouse = !freeMouse;
			default:
				break;
			}
			});

		if (this->window->Open())
		{
			window->GetSize(width, height);
			// set clear color (Background color)
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("VertShader.glsl","FragShader.glsl");

			// Find object textures
			objTexture = std::make_shared<TextureResource>("cubepic.png");
			// Load object textures
			objTexture->LoadFromFile();
			// Object meshes
			objMesh = MeshResource::LoadObj("cube");

			gnodeObj = GraphicsNode (objMesh, objTexture, shaders, posMat);
			return true;
		}
		return false;
	}

	void ExampleApp::Run()
	{
 		// Create camera
		camera.Setup(90, width, height, 0.001, 100);
		camera.SetPosition(cameraPos);

		// Create light source
		std::vector<Lighting> lights;
		Lighting light(VectorMath3(0, 0, 5), VectorMath3(1, 1, 1), 5);
		lights.push_back(light);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");
		double x = 0, y = 0;
	
		while (this->window->IsOpen())
		{
			if(freeMouse){
				glfwGetCursorPos(window->window, &x, &y);
				rotMat = RotateMatrix(((height/2)-y) * -speed, VectorMath3(1, 0, 0)) * RotateMatrix(((width/2)-x) * -speed, VectorMath3(0,1,0));
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();
			
			if (forward)
			{
				cameraPos = cameraPos + camera.GetVectorZ() * mvmtSpeed;
			}
			else if (backward)
			{
				cameraPos = cameraPos - camera.GetVectorZ() * mvmtSpeed;
			}
			if (left)
			{
				VectorMath3 cameraX = camera.GetVectorX();
				cameraPos = cameraPos - VectorMath3(cameraX.x, 0, cameraX.z) * mvmtSpeed;
			}
			else if (right)
			{
				VectorMath3 cameraX = camera.GetVectorX();
				cameraPos = cameraPos + VectorMath3(cameraX.x, 0, cameraX.z) * mvmtSpeed;
			}
			if (up)
			{
				cameraPos = cameraPos + VectorMath3(0,1,0) * mvmtSpeed;
			}
			else if (down)
			{
				cameraPos = cameraPos - VectorMath3(0,1,0) * mvmtSpeed;
			}
			// Update camera pos

			camera.SetPosition(cameraPos);
			//camera.SetRotation(cameraRotation);
			camera.SetRotMat(rotMat);
			shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");

			// Rendering
			if(debug){
				Debug::CreateGrid(100, VectorMath4(0,0.3,0.3,1));
				ShootFromMousePos();
			}

			for (int i = 0; i < mathLines.size(); i++){
				Debug::DrawLine(mathLines[i], VectorMath4(1,0,0,1));
			}

			Light::bindLights(shaders, lights);

			gnodeObj.Draw();

			Debug::Render(camera.GetProjViewMatrix());

			this->window->SwapBuffers();
		}
	}
}