//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
//#include <stb_image.h>
#define AMOUNT_OF_LIGHTS 10
#define AMOUNT_OF_OBJECTS 10

#include <cstring>
#include "config.h"
#include "TestApp.h"
#include "render/GBuffer.h"
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

	void ExampleApp::MoveCamera(VectorMath3 &cameraPos){
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
	}

	bool ExampleApp::Open()
	{
	
		App::Open();
		this->window = new Display::Window;

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
			default:
				break;
			}
			});

		if (this->window->Open())
		{
			window->GetSize(width, height);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("VertGLTFShader.glsl","FragGLTFShader.glsl");
			pointLightShaders = std::make_shared<ShaderResource>();
			pointLightShaders->LoadShader("PointLightVertexShader.glsl","PointLightFragShader.glsl");
			directionalLightShaders = std::make_shared<ShaderResource>();
			directionalLightShaders->LoadShader("DirectionalLightVertexShader.glsl","DirectionalLightFragShader.glsl");

			// randomize what objects should be rendered
			for (int i = 0; i < AMOUNT_OF_OBJECTS; i++)
			{
				switch (rand() % 4)
				{
				case 0:
					gltfModel = GraphicsNode(gltfMesh, "wooden_crate_tangents.glb", shaders, MatrixMath::TranslationMatrix(VectorMath3((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 40) - 20)));
					break;
				case 1:
					gltfModel = GraphicsNode(gltfMesh, "mokey.gltf", shaders, MatrixMath::TranslationMatrix(VectorMath3((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 40) - 20)) * RotateMatrix(M_PI / 2, VectorMath3(1, 0, 0)));
					break;
				case 2:
					gltfModel = GraphicsNode(gltfMesh, "hacha.glb", shaders, MatrixMath::TranslationMatrix(VectorMath3((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 40) - 20)));
					break;
				case 3:
					gltfModel = GraphicsNode(gltfMesh, "capybara_low_poly.glb", shaders, MatrixMath::TranslationMatrix(VectorMath3((rand() % 40) - 20, (rand() % 40) - 20, (rand() % 40) - 20)));
					break;
				default:
					break;
				}

				objectArray.push_back(gltfModel);
			}

			return true;
		}
		return false;
	}

	void ExampleApp::Run()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GBuffer gbuffer;
		gbuffer.Init(width, height);
		std::cout << glGetError() << std::endl;

 		// Create camera
		camera.Setup(90, width, height, 0.001, 100);
		camera.SetPosition(cameraPos);

		// Create light sources
		std::vector <Lighting> pointLights;
		for (int i = 0; i < AMOUNT_OF_LIGHTS; i++)
		{

			Lighting pointLight(VectorMath3((rand() % 50)-25, (rand() % 40) - 20, (rand() % 40) - 20), VectorMath3(1, 1, 1), 0.1, MeshResource::LoadObj("icosphere", 10));
			pointLights.push_back(pointLight);
		}
		Lighting directionalLight(VectorMath3(0, 1000, 50), VectorMath3(1, 1, 1), 0.001, MeshResource::DirLightQuad());

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");
		double x = 0, y = 0;
		float lightMove = 0;
		VectorMath3 lightPos = VectorMath3(0,0,0);
		while (this->window->IsOpen())
		{
			// move light sources
			lightMove += 0.001f;
			for (int i = 0; i < AMOUNT_OF_LIGHTS; i++)
			{
				VectorMath3 pointLightOriginPos = pointLights[i].getOriginPos();
				pointLights[i].setPos(VectorMath3(pointLightOriginPos.x * cos(lightMove), pointLightOriginPos.y, pointLightOriginPos.z * sin(lightMove)));
			}

			glfwGetCursorPos(window->window, &x, &y);
			rotMat = RotateMatrix(((height/2)-y) * -speed, VectorMath3(1, 0, 0)) * RotateMatrix(((width/2)-x) * -speed, VectorMath3(0,1,0));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			gbuffer.Clear();
			this->window->Update();

			glClearColor(0.1, 0.1, 0.1, 1);

			// Update camera pos
			MoveCamera(cameraPos);
			camera.SetPosition(cameraPos);
			camera.SetRotMat(rotMat);
			gbuffer.Bind();
			shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");
			pointLightShaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");
			directionalLightShaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");

			//gltfModel.Draw();
			// draw objects
			for (int i = 0; i < objectArray.size(); i++)
			{
				objectArray[i].Draw();
			}

			gbuffer.Unbind();
			gbuffer.BindTexturesToShader(pointLightShaders);
			gbuffer.BindTexturesToShader(directionalLightShaders);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE,GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			glEnable(GL_CULL_FACE);
			directionalLight.RenderDirLight(directionalLightShaders, cameraPos, (float)width, (float)height, VectorMath3(0.5,1,0.25));
			glCullFace(GL_FRONT);
			for (int i = 0; i < AMOUNT_OF_LIGHTS; i++)
			{
				pointLights[i].Render(pointLightShaders, cameraPos, (float)width, (float)height);
			}
			glDisable(GL_BLEND);
			glCullFace(GL_BACK);

			
			glEnable(GL_DEPTH_TEST);

			// Debug Rendering
			if (debug) {
				Debug::CreateGrid(100, VectorMath4(0, 0.3, 0.3, 1));
				for (int i = 0; i < AMOUNT_OF_LIGHTS; i++)
				{
					Debug::DrawSquare(1, pointLights[i].getPos(), VectorMath4(0, 1, 0, 1));
				}
				VectorMath3 point, normal;
			}
			Debug::Render(camera.GetProjViewMatrix());

			this->window->SwapBuffers();
		}
	}
}