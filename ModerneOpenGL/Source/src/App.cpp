#include <Core/InputHandler.h>

#include "App.h"
#include "Model.h"
#include "Camera.h"
#include "Utils/Time.h"

Vector2D Application::oldMousePos = { 0.f,0.f };
Application* Application::instance = nullptr;
GLFWwindow* Application::window = nullptr;

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
}

void Application::InitCallbacks()
{
    /* Handle Keyboard & Mouse Inputs */
    glfwSetKeyCallback(Application::window, InputHandler::KeyboardCallback);
    glfwSetCursorPosCallback(Application::window, InputHandler::MouseCursorCallback);
    glfwSetMouseButtonCallback(Application::window, InputHandler::MouseButtonCallback);
}

void Application::InitResources()
{
    /* Resource Loading */
    ResourceManager::Get().Create<Model>("pyramid.obj");
    Model* m = ResourceManager::Get().Get<Model>("pyramid.obj");
    ResourceManager::Get().Create<Model>("AlienAnimal.obj");
    Model* m2 = ResourceManager::Get().Get<Model>("AlienAnimal.obj");
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
    glClear(GL_COLOR_BUFFER_BIT);
    
    Model* pyramid = ResourceManager::Get().Get<Model>("pyramid.obj");
    pyramid->vertexAttributes.Bind();
    pyramid->vbo.Bind(GL_ARRAY_BUFFER);
    pyramid->vbo.SetData(GL_ARRAY_BUFFER, sizeof(Vertex) * pyramid->vertices.size(), pyramid->vertices.data(), GL_STATIC_DRAW);

    pyramid->ebo.Bind(GL_ELEMENT_ARRAY_BUFFER);
    pyramid->ebo.SetData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pyramid->indexes.size(), pyramid->indexes.data(), GL_STATIC_DRAW);
    pyramid->vertexAttributes.SetAttributes(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(0));
    pyramid->vertexAttributes.SetAttributes(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(3 * sizeof(float)));
    pyramid->vertexAttributes.SetAttributes(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(6 * sizeof(float)));

    pyramid->vertexAttributes.Bind();

}

void Application::SetWindowSize(float width, float height)
{
    m_width = width;
    m_height = height;
    Camera::Get().recalculateProjection = true;
}


void Application::RotationMouse()
{
    Camera* cam = &Camera::Get();
    Vector2D newMousePos = InputHandler::GetMousePos();

    Vector2D dirMouse = Application::oldMousePos - newMousePos;

    Vector3D localAxisX3D = Normalize(CrossProduct(Vector3D::axeY, cam->GetDirection()));

    cam->Rotation(dirMouse.x / 500.f, Vector3D::axeY, cam->GetEye());
    cam->Rotation(dirMouse.y / 500.f, localAxisX3D, cam->GetEye());
    Application::oldMousePos = newMousePos;
}