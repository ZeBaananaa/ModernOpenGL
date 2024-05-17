#pragma once
#include "MathPerso.h"
#include "Shader.h"
#include "Utils/WindowHandler.h"
#include "Light.h"
#include "Utils/InputHandler.h"
#include "Model.h"
#include "Camera.h"
#include "Utils/Time.h"
#include "SceneGraph.h"
#include "Resources/Texture.h"
#include "GameObject.h"

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

    GameObject* InitSceneObjects();
    void AnimateScene(GameObject* object);
    GameObject* root;
};