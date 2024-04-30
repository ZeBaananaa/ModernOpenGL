#include <Core/InputHandler.h>

#include "App.h"
#include "Model.h"

#include "Camera.h"

Vector2D Application::oldMousePos = { 0.f,0.f };
double Application::deltaTime = 0.f;
Application* Application::instance = nullptr;

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

bool Application::Initialise()
{
    shader.SetVertexShader("Assets/Shaders/Example_Shader.vert");
    shader.SetFragmentShader("Assets/Shaders/Example_Shader.frag");
    shader.Link();

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);

    glBindVertexArray(m_VAO);
    // array car utilise par glDrawArrays()
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    //if data == null juste alloue memoire
  //  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexes.size(0, g_Indices, GL_STATIC_DRAW);

#define POSITION 0
#define NORMAL 3
#define Texture 4
    // indice vbo si plusieur vbo (pos,couleur,ect.) ici tout dans 1 /nbcomposants/type composants/noramaliser?/size of struct
  
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(POSITION);

    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(NORMAL);

    glVertexAttribPointer(Texture, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
    glEnableVertexAttribArray(Texture);

#undef POSITION
#undef NORMAL
#undef Texture

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
    UpdateDeltaTime();
    Camera::Get().Update();
    RotationMouse();
    Render();
}

void Application::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(m_VAO);

    //draw arrays ou elements
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void Application::UpdateDeltaTime()
{
    std::chrono::duration<double> newEnd = std::chrono::steady_clock::now() - end;
    end = std::chrono::steady_clock::now();


    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(newEnd);
    deltaTime = newEnd.count();
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