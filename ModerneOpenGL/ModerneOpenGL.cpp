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
	InitWindow();

	Application::Get().Initialise();

	SceneGraph::Get();

	GameObject* c1 = new GameObject({ -5,0,0 }, Vector3D::zero, Vector3D::one * 0.5, "sphere.obj", "black.png");
	GameObject* c0 = new GameObject(Vector3D::zero, Vector3D::zero, Vector3D::one * 0.1f, "Alien.obj", "alien.jpg");
	GameObject* c2 = new GameObject({ 5,0,0 }, Vector3D::zero, Vector3D::one, "pyramid.obj", "baboon.jpg");
	GameObject* c3 = new GameObject({ 10,0,0 }, {90,0,0}, Vector3D::one, "cube.obj", "alien.jpg");
	GameObject* c4 = new GameObject({ -20,0,0 }, {90,0,0}, Vector3D::one, "shield.obj", "shield.png");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Application::Get().window) && !InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		/* Render here */
		Application::Get().Update();

		/* Swap front and back buffers */
		glfwSwapBuffers(Application::Get().window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Destroy();
	return 0;
}