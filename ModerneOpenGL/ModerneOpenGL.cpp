// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Assertion.h"
#include "Log.h"
#include "App.h"
#include "Camera.h"
#include "Model.h"
#include "MathPerso.h"
#include "App.h"
#include "Utils/InputHandler.h"

#include "GameObject.h"
#include "Components.h"
#include "SceneGraph.h"
#include "Menu.h"

#include <iostream>

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
	Menu::Get().Destroy();
}

void InitWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Modern OpenGL", NULL, NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	if (!window)
	{
		DEBUG_LOG("Cannot create GLFW Window... \nAborting!\n");
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	/* Init glad after context is defined */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG_LOG("Failed to initialize GLAD... \nAborting!\n");
		return;
	};

	glEnable(GL_DEPTH_TEST); /* Enable Depth Testing */
	glEnable(GL_CULL_FACE); /* Enable face culling & set it to back faces (Helps improve performances) */
	glCullFace(GL_BACK);

	Application::Get().window = window;

	Menu::Get().Init();
	Application::Get().Initialise();
	SceneGraph::Get();
}

void LoadScene()
{
}

int main()
{
	//#ifndef NDEBUG
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	//_CrtSetBreakAlloc(699402);
	//#endif

	InitWindow();

	GameObject* sun = new GameObject(Vector3D::zero, Vector3D(0.f, 0.f, 13.5f), Vector3D(2.5f), "sun.obj", "sun.jpg", "Sun");
	 
	GameObject* mercury = new GameObject(Vector3D(2.f, 0.f, -0.25f), Vector3D::zero, Vector3D(0.25f), "mercury.obj", "mercury.jpg", "Mercury", sun->transform);

	GameObject* venus = new GameObject(Vector3D(-3.5f, 0.f, 0.25f), Vector3D::zero, Vector3D(0.4f), "venus.obj", "venus.jpg", "Venus", sun->transform);

	GameObject* earth = new GameObject(Vector3D(2.5f, 0.f, 2.35f), Vector3D::zero, Vector3D(0.4f), "earth.obj", "earth.jpg", "Earth", sun->transform);

	GameObject* moon = new GameObject(Vector3D(2.f, 0.f, 1.f), Vector3D::zero, Vector3D(0.25f), "moon.obj", "moon.jpg", "Moon", earth->transform);

	GameObject* mars = new GameObject(Vector3D(-4.f, 0.f, 1.5f), Vector3D::zero, Vector3D(0.375f), "mars.obj", "mars.jpg", "Mars", sun->transform);

	GameObject* jupiter = new GameObject(Vector3D(7.5f, 0.f, -2.f), Vector3D::zero, Vector3D(0.65f), "jupiter.obj", "jupiter.jpg", "Jupiter", sun->transform);

	GameObject* saturn = new GameObject(Vector3D(-9.5, 0.f, -1.5f), Vector3D::zero, Vector3D(0.60f), "saturn.obj", "saturn.jpg", "Saturn", sun->transform);
	GameObject* saturn_ring = new GameObject(Vector3D::zero, Vector3D(0.f, 0.f, -20.f), Vector3D(1.f), "saturn_ring.obj", "saturn_ring.png", "Saturn Ring", saturn->transform);

	GameObject* uranus = new GameObject(Vector3D(11.f, 0.f, 2.35f), Vector3D::zero, Vector3D(0.50f), "uranus.obj", "uranus.jpg", "Uranus", sun->transform, GL_CLAMP_TO_EDGE);

	GameObject* neptun = new GameObject(Vector3D(-12.f, 0.f, 3.f), Vector3D::zero, Vector3D(0.5f), "neptun.obj", "neptun.jpg", "Neptun", sun->transform);

	//GameObject* obj0 = new GameObject(Vector3D::zero, Vector3D::zero, Vector3D::one * 0.1f, "Alien.obj", "alien.png", "Alien");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Application::Get().window) && !InputHandler::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		Application::Get().Update();

		// TODO : Multiply with delta time
		sun->transform->SetLocalRotation(sun->transform->GetLocalRotation() + Vector3D(0.f, 0.1f, 0.f));
		for (auto ch = sun->transform->GetChildren().begin(); ch != sun->transform->GetChildren().end(); ++ch)
		{
			if ((*ch)->GetName() == "Earth")
			{
				(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + Vector3D(0.f, 0.f, 0.25f));

				for (auto ch2 = (*ch)->GetChildren().begin(); ch2 != (*ch)->GetChildren().end(); ++ch2)
					(*ch2)->SetLocalRotation((*ch2)->GetLocalRotation() + Vector3D(0.f, 0.f, 1.5f));
			}
			else if ((*ch)->GetName() == "Saturn")
				(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + Vector3D(0.f, 0.45f, 0.f));
			else
				(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + Vector3D(0.2f, 0.2f, 0.f));
		}

		Menu::Get().Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(Application::Get().window);

		if (InputHandler::IsKeyPressed(GLFW_KEY_M))
			Application::Get().lightManager->SetSpotAngle(SpotLights::SP0, -1, true);

		if (InputHandler::IsKeyPressed(GLFW_KEY_P))
			Application::Get().lightManager->SetSpotAngle(SpotLights::SP0, 1, true);

		InputHandler::ProcessPressedKeys();
	}
	Destroy();
	return 0;
}