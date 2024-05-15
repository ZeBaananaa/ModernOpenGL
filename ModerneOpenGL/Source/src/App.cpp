#include "App.h"

Vector2D Application::oldMousePos = { 0.f,0.f };
Application* Application::instance = nullptr;

Application::~Application()
{
	if (instance->lightManager)
	{
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
	/* DEFAULT SHADER */
	shader.SetVertex("Assets/Shaders/Default.vert");
	shader.SetFragment("Assets/Shaders/Default.frag");
	shader.Link();

	glGenBuffers(1, &instance->lightManager->ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, instance->lightManager->ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightManager), lightManager, GL_DYNAMIC_DRAW);

	unsigned int index = glGetUniformBlockIndex(shader.GetProgram(), "Lights");
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, instance->lightManager->ubo);

	/* SKYBOX SHADER */
	
	skybox.SetVertex("Assets/Shaders/Skybox.vert");
	skybox.SetFragment("Assets/Shaders/Skybox.frag");
	skybox.Link();

	glUniform1i(glGetUniformLocation(Application::Get().skybox.GetProgram(), "viewPos"), 0);
}

void Application::InitCallbacks()
{
	/* Handle Keyboard & Mouse Inputs */
	glfwSetKeyCallback(Application::window, InputHandler::KeyboardCallback);
	glfwSetCursorPosCallback(Application::window, InputHandler::MouseCursorCallback);
	glfwSetMouseButtonCallback(Application::window, InputHandler::MouseButtonCallback);
	glfwSetScrollCallback(Application::window, InputHandler::MouseScrollCallback);

	/* Window resizing & framebuffer callbacks */
	glfwSetFramebufferSizeCallback(Application::window, WindowHandler::BufferResizeCallback);
	glfwSetWindowSizeCallback(Application::window, WindowHandler::WindowResizeCallback);
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
	model->vertexAttributes.SetAttributes(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::textureUV));
	model->vertexAttributes.SetAttributes(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
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
		InitModel(entry.path().filename().string());

	for (const auto& txtEntry : std::filesystem::directory_iterator(txtPath))
		InitTexture(txtEntry.path().filename().string());
}

bool Application::Initialise()
{
	lightManager = new LightManager();
	lightManager->Init();

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
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.15f, 0.15f, 1.f, 1.f); // Set background color to blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shader.GetProgram());
	//glUseProgram(skybox.GetProgram());
	SceneGraph::Get().Render();
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