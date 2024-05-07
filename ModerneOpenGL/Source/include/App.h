#pragma once
#include "MathPerso.h"
#include "Shader.h"
#include "Utils/WindowHandler.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Application
{
public:
     ~Application() = default;

     static Application& Get();
     static void Destroy();
     GLFWwindow* window;

    int32_t m_width = 1280;
    int32_t m_height = 720;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLuint m_VAO = 0;

    bool Initialise();
    void Terminate();
    void Update();
    void Render();

    static Vector2D oldMousePos;
    void RotationMouse();

    Shader shader;
private:
    static Application* instance;
    Application() = default;

    void InitShaders();
    void InitResources();
    void InitCallbacks();

};