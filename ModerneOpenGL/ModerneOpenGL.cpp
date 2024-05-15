// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "Assertion.h"
//#include <cstdint>
#include "Log.h"
#include "App.h"
#include "Camera.h"
#include "Model.h"
#include "MathPerso.h"
#include "App.h"
#include "Utils/InputHandler.h"

#include "glad/glad.h"
#include <iostream>

#include "GameObject.h"
#include "Components.h"
#include "SceneGraph.h"

void Destroy()
{
	Application::Get().Terminate();
	glfwTerminate();

	Log::Destroy();
	Application::Destroy();
	Camera::Destroy();
	ResourceManager::Destroy();
	Log::Destroy();
	SceneGraph::Destroy();
	InputHandler::Destroy();
}

void InitWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Modern OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Cannot create GLFW Window... \nAborting!" << std::endl;
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Init glad after context is defined */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD... \nAborting!" << std::endl;
		return;
	}

	/* Enable Depth Testing */
	glEnable(GL_DEPTH_TEST);

	/* Enable face culling & set it to back faces (Helps improve performances) */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Application::Get().window = window;
}


int main()
{
	//#ifndef NDEBUG
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	//_CrtSetBreakAlloc(699402);
	//#endif
	
	InitWindow();

	Application::Get().Initialise();

	SceneGraph::Get();
	
	GameObject* start0 = new GameObject({ 0,5,0.5 }, Vector3D::zero, Vector3D::one * 0.5, "sphere.obj", "black.png");
	GameObject* c1 = new GameObject(start0->transform->GetGlobalPosition(), Vector3D::zero, Vector3D::one * 0.5, "sphere.obj", "black.png");
	GameObject* c2 = new GameObject({ 0,0,0 }, { 180,0,0}, {1,1,1}, "cube.obj", "black.png");

	c1->AddComponent(AddCollider(Colliders::SPHERE, c1));
	c2->AddComponent(AddCollider(Colliders::CUBE, c2));

	SceneGraph::Get().Update();

	c1->transform->SetLocalPosition({0,-4,0.5});
	GameObject* c3 = new GameObject(c1->transform->GetLocalPosition(), { 0,0,0 }, Vector3D::one * 0.2, "sphere.obj", "black.png");

	if (CollisionSphereBox(c1->GetComponent<SphereCollider>(), c2->GetComponent<BoxCollider>()))
	{
		c1->GetComponent<MeshRenderer>()->texture = ResourceManager::Get().Get<Texture>("missing_texture.jpg");
	}

	bool okm = false;
	bool okp = false;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Application::Get().window) && !InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		/* Render here */
		Application::Get().Update();

		/* Swap front and back buffers */
		glfwSwapBuffers(Application::Get().window);

		if (InputHandler::IsKeyReleased(GLFW_KEY_M) && okm == true)
			okm = false;

		if (InputHandler::IsKeyReleased(GLFW_KEY_P) && okp == true)
			okp = false;

		if (InputHandler::IsKeyPressed(GLFW_KEY_M) && okm == false)
		{
			okm = true;
			Application::Get().lightManager->SetSpotAngle(SpotLights::SP0, -1, true);

			DEBUG_LOG("%f", Application::Get().lightManager->GetSpotAngle(SpotLights::SP0));
		}
		if (InputHandler::IsKeyPressed(GLFW_KEY_P) && okp == false)
		{
			okp = true;
			Application::Get().lightManager->SetSpotAngle(SpotLights::SP0, 1, true);

			DEBUG_LOG("%f", Application::Get().lightManager->GetSpotAngle(SpotLights::SP0));
		}

		/* Poll for and process events */
		glfwPollEvents();
	}

	Destroy();
	return 0;
}