#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MathPerso.h"
#include "Shader.h"
#include "Utils/WindowHandler.h"
#include "Light.h"

class Application
{
public:
     ~Application();

     LightManager* lightManager;

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