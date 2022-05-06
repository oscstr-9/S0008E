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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("VertGLTFShader.glsl","FragGLTFShader.glsl");

			// Find object textures
			gltfModel = GraphicsNode(gltfMesh, "wooden_crate_tangents.glb",  shaders, MatrixMath::TranslationMatrix(VectorMath3(0,5,0)) * RotateMatrix(M_PI/2, VectorMath3(1,0,0)));


			// Load object textures
			// Object meshes
			return true;
		}
		return false;
	}

	void ExampleApp::Run()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint deferredFBO;
		glGenFramebuffers(1, &deferredFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, 	deferredFBO);

		GLuint colorTexture;
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, width,height, 0, GL_RGB, GL_UNSIGNED_INT, /*void* pixels*/);
		glFramebufferTexture2D(deferredFBO, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

		GLuint normalTexture;
		glGenTextures(1, &normalTexture);
		glBindTexture(GL_TEXTURE_2D, normalTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, width,height, 0, GL_RGB, GL_UNSIGNED_INT, /*void* pixels*/);
		glFramebufferTexture2D(deferredFBO, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);

		GLuint worldPosTexture;
		glGenTextures(1, &worldPosTexture);
		glBindTexture(GL_TEXTURE_2D, worldPosTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, width,height, 0, GL_RGB, GL_UNSIGNED_INT, /*void* pixels*/);
		glFramebufferTexture2D(deferredFBO, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, worldPosTexture, 0);

		GLuint depthTexture;
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, width,height, 0, GL_RGB, GL_UNSIGNED_INT, /*void* pixels*/);
		glFramebufferTexture2D(deferredFBO, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);


 		// Create camera
		camera.Setup(90, width, height, 0.001, 100);
		camera.SetPosition(cameraPos);

		// Create light source
		Lighting light(VectorMath3(0, 0, 5), VectorMath3(1, 1, 1), 0.1);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");
		double x = 0, y = 0;
		float i = 0;
		while (this->window->IsOpen())
		{
			i+=0.01f;
			light.setPos(VectorMath3(cos(i), 5/5, sin(i)) * 5);
			glfwGetCursorPos(window->window, &x, &y);
			rotMat = RotateMatrix(((height/2)-y) * -speed, VectorMath3(1, 0, 0)) * RotateMatrix(((width/2)-x) * -speed, VectorMath3(0,1,0));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			// Update camera pos
			MoveCamera(cameraPos);
			camera.SetPosition(cameraPos);
			camera.SetRotMat(rotMat);
			shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");

			// Rendering
			if(debug){
				Debug::CreateGrid(100, VectorMath4(0,0.3,0.3,1));
				Debug::DrawSquare(2,VectorMath3(cos(i), 5/5, sin(i))*5, VectorMath4(0,1,0,1));
				VectorMath3 point, normal;
			}

			Light::bindLight(shaders, light, cameraPos);

			Debug::Render(camera.GetProjViewMatrix());

			gltfModel.Draw();

			this->window->SwapBuffers();
		}
	}
}