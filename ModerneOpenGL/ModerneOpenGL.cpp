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

float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};


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


int main()
{
	//#ifndef NDEBUG
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	//_CrtSetBreakAlloc(699402);
	//#endif
	
	InitWindow();

	GameObject* obj0 = new GameObject(Vector3D::zero, Vector3D::zero, Vector3D::one * 0.1f, "Alien.obj", "alien.png", "Alien");
	GameObject* obj1 = new GameObject(Vector3D(-5.f, 0.f, 5.f), Vector3D::zero, Vector3D(5.f), "sphere.obj", "", "Sphere", obj0->transform);

	GameObject* empty = new GameObject(SceneGraph::Get().root, "All Cubes");
	for (size_t i = 0; i < 11; i++)
		for (size_t j = 0; j < 11; j++)
			GameObject* cube = new GameObject({ i * 1.5f - 7.5f, j * 1.5f - 7.5f, 0.f }, { 0.f, 0.f, 0.f },
												Vector3D::one, "cube.obj", "", "", empty->transform);

	ResourceManager::Get().Create<Texture>("right.png");
	ResourceManager::Get().Create<Texture>("left.png");
	ResourceManager::Get().Create<Texture>("top.png");
	ResourceManager::Get().Create<Texture>("bottom.png");
	ResourceManager::Get().Create<Texture>("front.png");
	ResourceManager::Get().Create<Texture>("back.png");

	Texture* t1 = ResourceManager::Get().Get<Texture>("right.png");
	Texture* t2 = ResourceManager::Get().Get<Texture>("left.png");
	Texture* t3 = ResourceManager::Get().Get<Texture>("top.png");
	Texture* t4 = ResourceManager::Get().Get<Texture>("bottom.png");
	Texture* t5 = ResourceManager::Get().Get<Texture>("front.png");
	Texture* t6 = ResourceManager::Get().Get<Texture>("back.png");

	Cubemap* skybox = new Cubemap((*t1), (*t2), (*t3), (*t4), (*t5), (*t6));

	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Application::Get().window) && !InputHandler::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		/* Poll for and process events */
		glfwPollEvents();

		/* Render here */
		Application::Get().Update();

		Menu::Get().Render();

		glDepthFunc(GL_LEQUAL);

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