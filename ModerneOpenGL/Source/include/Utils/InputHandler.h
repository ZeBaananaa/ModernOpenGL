#pragma once

#include "MathPerso.h"

#include "glad/glad.h"
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
    static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyReleased(int key);

    static int GetKey();

    static bool IsMousePressed(int button);
    static bool IsMouseReleased(int button);

    static void SetMouseScrolling(double x, double y);
    static Vector2D IsMouseScrolling();

    static void SetMousePos(double x, double y);
    static Vector2D GetMousePos();
    static void ProcessPressedKeys();

private:
    static std::vector<int> m_CurrentKeyStatus;
    static std::vector<int> m_pressedKey;
    static std::vector<int> m_MouseButtonKeyStatus;
    static int keyPressed;

    static Vector2D mousePos;
    static Vector2D wheelPos;
}; 