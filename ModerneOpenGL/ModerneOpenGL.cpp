// ModerneOpenGL.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "Assertion.h"
//#include <cstdint>
#include "Log.h"
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
		return -EXIT_FAILURE;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Init glad after context is defined */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD... \nAborting!" << std::endl;
		return -EXIT_FAILURE;
	}

	/* Handle Keyboard & Mouse Inputs */
	glfwSetKeyCallback(window, InputHandler::KeyboardCallback);
	glfwSetCursorPosCallback(window, InputHandler::MouseCallback);

	Application app;
	app.Initialise();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Set background color to blue
		glClearColor(0.15f, 0.15f, 1.f, 1.f);

		/* Render here */
		app.Update();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		if (InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE))
			return EXIT_SUCCESS;

		std::cout << "Mouse pos X : " << InputHandler::GetMousePos().x << std::endl;
		std::cout << "Mouse pos Y : " << InputHandler::GetMousePos().y << std::endl;

		/* Poll for and process events */
		glfwPollEvents();
	}

	app.Terminate();
	glfwTerminate();
	return 0;
}

int main()
{
	Init();

	Log::Get().Destroy();

	return EXIT_SUCCESS;
}