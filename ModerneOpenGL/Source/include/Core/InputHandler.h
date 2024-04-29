#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "MathPerso.h"

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler();

    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyReleased(int key);
    static bool IsKeyUnused(int key);

    static void SetMousePos(float x, float y)
    {
        mousePos.x = x;
        mousePos.y = y;
    };

    static Vector2D GetMousePos()
    {
        return mousePos;
    }

private:
    static std::vector<int> m_CurrentKeyStatus;
    static std::vector<int> m_OldKeyStatus;

    static Vector2D mousePos;
}; 