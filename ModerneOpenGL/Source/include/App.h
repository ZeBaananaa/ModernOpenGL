#pragma once
//si vous utilisez gle32s.lib (et donc pas de dll)
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MathPerso.h"

class Application
{
public:
     ~Application() = default;

     static Application& Get();
     static void Destroy();

    int32_t m_width = 1280;
    int32_t m_height = 720;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLuint m_VAO = 0;


    bool Initialise();
    void Terminate();
    void Update();
    void Render();

    void SetWindowSize(float width, float height);

    static Vector2D posMouse;
    void RotationMouse(int x, int y);

private:
    static Application* instance;
    Application() = default;
};

//Vertex g_Triangles[] = { Vertex{{-0.5f,-0.5f},   {1.f,0.f,0.f}},
//                            Vertex{{0.5f,-0.5f},    {0.f,1.f,0.f}},
//                            Vertex{{0.f,0.5f},      {0.f,0.f,1.f}}
//};
//
//Vertex sablier[] = { g_Triangles[0],     g_Triangles[1],    g_Triangles[2],
//
//                    Vertex{{-0.5f,1.f},   {1.f,0.f,0.f}},
//                    Vertex{{0.5f,1.f},    {0.f,1.f,0.f}},
//                    Vertex{{0.f,0.25f},      {0.f,0.f,1.f}}
//};
//
//uint16_t g_Indices[] = { 0,1,2 };
//
//uint16_t g_IndicesSablier[] = { 0,1,5,4,3,5 };