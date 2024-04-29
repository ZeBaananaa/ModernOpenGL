#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <map>

class InputHandler
{
public:
    InputHandler() = default;
    ~InputHandler() = default;

    virtual void OnKeyPressed(int key) = 0;
    virtual void OnKeyReleased(int key) = 0;
};