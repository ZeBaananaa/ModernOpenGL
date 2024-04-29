#pragma once
#include "InputHandler.h"
#include <Windows.h>
#include <map>

class InputSystem
{
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void Process();
    void AddHandler(InputHandler* inputHandler);
    void RemoveHandler(InputHandler* inputHandler);

    static InputSystem* get();

private:
    std::map<InputHandler*, InputHandler*> m_handlers;
};