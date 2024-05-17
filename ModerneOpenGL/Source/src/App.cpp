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

	root = InitSceneObjects();

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
	SceneGraph::Get().Update();
	Render();

	AnimateScene(root);
}

void Application::Render()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.f, 0.01f, 0.12f, 1.f); // Set background color to blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.GetProgram());
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

GameObject* Application::InitSceneObjects()
{
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

	GameObject* alien = new GameObject(Vector3D::zero, Vector3D::zero, Vector3D::one * 0.01f, "Alien.obj", "alien.png", "Alien");

	return sun;
}

void Application::AnimateScene(GameObject* object)
{
	object->transform->SetLocalRotation(object->transform->GetLocalRotation() + (Vector3D(0.f, 10.f, 0.f) * Time::DeltaTime()));
	for (auto ch = object->transform->GetChildren().begin(); ch != object->transform->GetChildren().end(); ++ch)
	{
		if ((*ch)->GetName() == "Earth")
		{
			(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + (Vector3D(0.f, 0.f, 25.f) * Time::DeltaTime()));

			for (auto ch2 = (*ch)->GetChildren().begin(); ch2 != (*ch)->GetChildren().end(); ++ch2)
				(*ch2)->SetLocalRotation((*ch2)->GetLocalRotation() + (Vector3D(0.f, 75.f, 75.f) * Time::DeltaTime()));
		}
		else if ((*ch)->GetName() == "Saturn")
			(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + (Vector3D(0.f, 45.f, 0.f) * Time::DeltaTime()));
		else
			(*ch)->SetLocalRotation((*ch)->GetLocalRotation() + (Vector3D(20.f, 20.f, 0.f) * Time::DeltaTime()));
	}
}