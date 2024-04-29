#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyReleased(int key);

private:
    static std::vector<int> m_CurrentKeyStatus;
    static std::vector<int> m_OldKeyStatus;
}; 