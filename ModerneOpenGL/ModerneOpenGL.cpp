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

int Init()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Modern OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Cannot create GLFW Window... \nAborting!" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Init glad after context is defined */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD... \nAborting!" << std::endl;
		return -1;
	}

	/* Handle Keyboard & Mouse Inputs */
	glfwSetKeyCallback(window, InputHandler::KeyboardCallback);
	glfwSetCursorPosCallback(window, InputHandler::MouseCursorCallback);
	glfwSetMouseButtonCallback(window, InputHandler::MouseButtonCallback);	

	Application::Get().Initialise();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && !InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		// Set background color to blue
		glClearColor(0.15f, 0.15f, 1.f, 1.f);

		/* Render here */
		Application::Get().Update();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Application::Get().Terminate();
	glfwTerminate();
	return 0;
}

int main()
{
    ResourceManager::Get().Create<Model>("pyramid.obj");
    Model* m =ResourceManager::Get().Get<Model>("pyramid.obj");
    ResourceManager::Get().Create<Model>("AlienAnimal.obj");
	Model* m2 = ResourceManager::Get().Get<Model>("AlienAnimal.obj");

	Init();

    //DEBUG_LOG(Camera::Get().GetProjectionMatrix().ToString());

    Log::Destroy();
    Application::Destroy();
    Camera::Destroy();
    ResourceManager::Destroy();
	Log::Get().Destroy();

	return 0;
}