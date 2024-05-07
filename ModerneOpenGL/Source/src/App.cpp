#include <Utils/InputHandler.h>

#include "App.h"
#include "Model.h"
#include "Camera.h"
#include "Utils/Time.h"
#include "SceneGraph.h"
#include <Resources/Texture.h>
#include "Light.h"

#include "glad/glad.h"

Vector2D Application::oldMousePos = { 0.f,0.f };
Application* Application::instance = nullptr;

Application::~Application()
{
	if (instance->lightManager)
	{
		instance->lightManager->Destroy();
		delete instance->lightManager;
		instance->lightManager = nullptr;
	}
}

Application& Application::Get()
{
	if (instance == nullptr)
		instance = new Application();
	return *instance;
}

void Application::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void Application::InitShaders()
{
	shader.SetVertexShader("Assets/Shaders/Example_Shader.vert");
	shader.SetFragmentShader("Assets/Shaders/Example_Shader.frag");
	shader.Link();

	
	//spot = new SpotLight();
	//spot->ubo = 0;

	//spot->u_float.x = 1;// = { 0,0,0,1 };
	//spot->u_float.y = 1;
	//spot->u_float.w = 1;
	/*
	spot->lightColor[0] = 1;
	spot->lightColor[1] = 1;
	spot->lightColor[2] = 1;
	spot->lightColor[3] = 1;*/

	/*spot->lightPosition = { 0,5,0,1 };
	spot->lightDirection = { 0,-1,0,0 };

	spot->lightAmbientColor = { 1.f,1.f,1.f,1.f };
	spot->lightDiffuseColor = { 1.f,1.f,1.f,1.f };
	spot->lightSpecularColor = { 1.f,1.f,1.f,1.f };*/

	/*glGenBuffers(1, &spot->ubo);

	unsigned int lights_index = glGetUniformBlockIndex(Application::Get().shader.GetProgram(), "SpotLight");
	glUniformBlockBinding(Application::Get().shader.GetProgram(), lights_index, 2);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, Application::Get().spot->ubo);


	glBindBuffer(GL_UNIFORM_BUFFER, spot->ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SpotLight), &spot, GL_STATIC_DRAW);*/

	glGenBuffers(1, &Application::Get().lightManager->ubo);

	unsigned int test_index = glGetUniformBlockIndex(Application::Get().shader.GetProgram(), "Test");
	glUniformBlockBinding(Application::Get().shader.GetProgram(), test_index, 2);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, Application::Get().lightManager->ubo);

	float value = 1;
	glBindBuffer(GL_UNIFORM_BUFFER, indexUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float) *10, &spot->ubo, GL_STATIC_DRAW);

	std::cout << sizeof(SpotLight) << " : " << glGetUniformBlockIndex(shader.GetProgram(), "SpotLight");

	//	glBindBufferBase(GL_UNIFORM_BUFFER, 4, spot->ubo);
}

void Application::InitCallbacks()
{
	/* Handle Keyboard & Mouse Inputs */
	glfwSetKeyCallback(Application::window, InputHandler::KeyboardCallback);
	glfwSetCursorPosCallback(Application::window, InputHandler::MouseCursorCallback);
	glfwSetMouseButtonCallback(Application::window, InputHandler::MouseButtonCallback);

	/* Window resizing & framebuffer callbacks */
	glfwSetWindowSizeCallback(Application::window, WindowHandler::WindowResizeCallback);
	glfwSetFramebufferSizeCallback(Application::window, WindowHandler::BufferResizeCallback);
}

void InitModel(std::string modelName)
{
	Model* model = ResourceManager::Get().Create<Model>(modelName);

	if (model == nullptr)
	{
		DEBUG_LOG("The model (" + modelName + ") doesn't exists!");
		return;
	}

	model->vertexAttributes.Bind();

	model->vbo.Bind(GL_ARRAY_BUFFER);
	model->vbo.SetData(GL_ARRAY_BUFFER, sizeof(Vertex) * model->vertices.size(), model->vertices.data(), GL_STATIC_DRAW);

	model->ebo.Bind(GL_ELEMENT_ARRAY_BUFFER);
	model->ebo.SetData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model->indexes.size(), model->indexes.data(), GL_STATIC_DRAW);
	model->vertexAttributes.SetAttributes(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(0));
	model->vertexAttributes.SetAttributes(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::textureUV));
	model->vertexAttributes.SetAttributes(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));


	/*
	//crreation UBO (uniform buffer)
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Block),
		uboData, GL_STREAM_DRAW);

	//commet relier un UBO et un block
	//1 choisir un binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, 42, UBO);
	//2 recuperer l index de l'uniform block
	int32_t index = glGetUniformBlockIndex(program, "Matrices");
	//3 relier le block et l UBO sur le binding point
	glUniformBlockBinding(program, index, 42);
	*/
}


void InitTexture(std::string textureName)
{
	Texture* texture = ResourceManager::Get().Create<Texture>(textureName);

	if (texture == nullptr)
	{
		DEBUG_LOG("The model (" + textureName + ") doesn't exists!");
		return;
	}
}

 void Application::InitResources()
{
	std::string path = "Assets/Meshes/";
	std::string txtPath = "Assets/Textures/";

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		InitModel(entry.path().filename().string());
		std::cout << entry.path().filename() << std::endl;
	}

	for (const auto& txtEntry : std::filesystem::directory_iterator(txtPath))
	{
		InitTexture(txtEntry.path().filename().string());
		std::cout << txtEntry.path().filename() << std::endl;
	}
}

bool Application::Initialise()
{
	InitResources();
	InitCallbacks();
	InitShaders();

	return true;
}

void Application::Terminate()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Application::Update()
{
	Time::Update();
	Camera::Get().Update();
	RotationMouse();
	Render();
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to blue
	glClearColor(0.15f, 0.15f, 1.f, 1.f);

	glUseProgram(shader.GetProgram());
	SceneGraph::Get().Render();
	//Model* alien = ResourceManager::Get().Get<Model>("Alien.obj");

	//Matrix4x4 MVP =  Camera::Get().GetVPMatrix() * TRS({ -10, -10, -10 }, { 0, 0, 0 }, { 10, 10, 10 });
	//float tab[16];
	//Matrix4x4ToFloat(MVP, tab);
	//glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "MVP"), 1, false, tab);

	//glDrawElements(GL_TRIANGLES, alien->indexes.size(), GL_UNSIGNED_INT, 0);
}

void Application::RotationMouse()
{
	Camera* cam = &Camera::Get();
	Vector2D newMousePos = InputHandler::GetMousePos();

	Vector2D dirMouse = Application::oldMousePos - newMousePos;

	Vector3D localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, cam->GetDirection()));

	if (InputHandler::IsMousePressed(GLFW_MOUSE_BUTTON_2))
	{
		/* Invert input direction to make movements more intuitive & user-friendly */
		cam->Rotation(dirMouse.x / 500.f, Vector3D::axeY, cam->GetEye());
		cam->Rotation(-dirMouse.y / 500.f, localAxisX3D, cam->GetEye());
	}
	Application::oldMousePos = newMousePos;
}