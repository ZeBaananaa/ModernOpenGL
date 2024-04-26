#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <map>

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void KeyCallback(int key, int action);
    bool GetKeyPressed(int key);
    bool GetKeyDown(int key);
};