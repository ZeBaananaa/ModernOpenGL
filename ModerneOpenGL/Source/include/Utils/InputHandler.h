#pragma once

#include "MathPerso.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <iostream>

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;

    static void Destroy();


    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseCursorCallback(GLFWwindow* window, double xpos, double ypos);

    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyHeld(int key);
    static bool IsKeyReleased(int key);

    static int GetKey();

    static bool IsMousePressed(int button);
    static bool IsMouseReleased(int button);

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
    static std::vector<int> m_MouseButtonKeyStatus;
    static int keyPressed;

    static Vector2D mousePos;
}; 