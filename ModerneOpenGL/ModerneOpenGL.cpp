// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "Assertion.h"
//#include <cstdint>
#include "Log.h"
#include "App.h"
#include "Camera.h"
#include "Model.h"
#include "MathPerso.h"
#include "App.h"
#include "InputHandler.h"

#include <glad/glad.h>
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
}

void InitWindow()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	Application::window = glfwCreateWindow(640, 480, "Modern OpenGL", NULL, NULL);
	if (!Application::window)
	{
		std::cout << "Cannot create GLFW Window... \nAborting!" << std::endl;
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(Application::window);

	/* Init glad after context is defined */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD... \nAborting!" << std::endl;
		return;
	}
}


int main()
{
	InitWindow();
	Application::Get().Initialise();

	SceneGraph::Get();

	GameObject* c0 = new GameObject({ 3,0,0 }, Vector3D::zero, Vector3D::one, "cube.obj");
	GameObject* c1 = new GameObject(Vector3D::axeX, { 0,45,0 }, { 0.5f,0.5f,0.5f }, "cube.obj", c0->transform);
	//GameObject* c2 = new GameObject({ 1.5f,0,0.5f }, {0, 0, 0},Vector3D::one, "cube.obj",c1->transform);

	DEBUG_LOG("global pos before : \n" + c1->transform->GetGlobalPosition().ToString() + " \n"
	+ "global rota before : \n" + c1->transform->GetGlobalRotation().ToString() + " \n"
	+ "global scale before : \n" + c1->transform->GetGlobalScale().ToString() + " \n");
	c1->transform->SetParent(SceneGraph::Get().root);
	DEBUG_LOG("global pos before : \n" + c1->transform->GetGlobalPosition().ToString() + " \n"
		+ "global rota before : \n" + c1->transform->GetGlobalRotation().ToString() + " \n"
		+ "global scale before : \n" + c1->transform->GetGlobalScale().ToString() + " \n");

	printf("\n");

	///* Loop until the user closes the window */
	//while (!glfwWindowShouldClose(Application::window) && !InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
	//{
	//	// Set background color to blue
	//	glClearColor(0.15f, 0.15f, 1.f, 1.f);

	//	/* Render here */
	//	Application::Get().Update();

	//	/* Swap front and back buffers */
	//	glfwSwapBuffers(Application::window);

	//	/* Poll for and process events */
	//	glfwPollEvents();
	//}

	Destroy();
	return 0;
}