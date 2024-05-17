// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Assertion.h"
//#include <cstdint>
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

#include <random>

int main()
{
	//#ifndef NDEBUG
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	//_CrtSetBreakAlloc(699402);
	//#endif

	InitWindow();

	GameObject* debugContainer = new GameObject(nullptr,"debugContainer");
	
	GameObject* s1 = new GameObject({ 5,5,10 }, Vector3D::zero, Vector3D::one * 0.2, "sphere.obj", "back.png","SphereCollider1");
	GameObject* s2 = new GameObject({ 5,10,0 }, Vector3D::zero, Vector3D::one * 0.2, "sphere.obj", "back.png", "SphereCollider2");
	GameObject* s3 = new GameObject({ 0,5,0 }, Vector3D::zero, Vector3D::one * 0.2, "sphere.obj", "back.png", "SphereCollider3");
	GameObject* s4 = new GameObject({ 10,0,-5 }, Vector3D::zero, Vector3D::one * 0.2, "sphere.obj", "back.png", "SphereCollider4");

	GameObject* c2 = new GameObject({ 5,5,0 }, { 0,45,0 }/* { 1.f * (rand() % 360), 1.f * (rand() % 360),1.f * (rand() % 360) }*/, { 1,1,1 }, "cube.obj", "bottom.png", "cube Collider");


	s1->AddComponent(AddCollider(Colliders::SPHERE, s1));
	s2->AddComponent(AddCollider(Colliders::SPHERE, s2));
	s3->AddComponent(AddCollider(Colliders::SPHERE, s3));
	s4->AddComponent(AddCollider(Colliders::SPHERE, s4));
	c2->AddComponent(AddCollider(Colliders::CUBE, c2));

	SceneGraph::Get().Update();

	s1->transform->SetLocalPosition(c2->transform->GetLocalPosition());
	s2->transform->SetLocalPosition(c2->transform->GetLocalPosition());
	s3->transform->SetLocalPosition(c2->transform->GetLocalPosition());
	s4->transform->SetLocalPosition(c2->transform->GetLocalPosition());

	if (CollisionSphereBox(s1->GetComponent<SphereCollider>(), c2->GetComponent<BoxCollider>()))
	{
		s1->GetComponent<MeshRenderer>()->texture = ResourceManager::Get().Get<Texture>("missing_texture.png");
	}
	if (CollisionSphereBox(s2->GetComponent<SphereCollider>(), c2->GetComponent<BoxCollider>()))
	{
		s2->GetComponent<MeshRenderer>()->texture = ResourceManager::Get().Get<Texture>("missing_texture.png");
	}
	if (CollisionSphereBox(s3->GetComponent<SphereCollider>(), c2->GetComponent<BoxCollider>()))
	{
		s3->GetComponent<MeshRenderer>()->texture = ResourceManager::Get().Get<Texture>("missing_texture.png");
	}
	if (CollisionSphereBox(s4->GetComponent<SphereCollider>(), c2->GetComponent<BoxCollider>()))
	{
		s4->GetComponent<MeshRenderer>()->texture = ResourceManager::Get().Get<Texture>("missing_texture.png");
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Application::Get().window) && !InputHandler::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		Application::Get().Update();

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