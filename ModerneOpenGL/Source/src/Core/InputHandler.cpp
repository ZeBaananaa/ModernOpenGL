#include "InputHandler.h"

std::vector<int> InputHandler::m_CurrentKeyStatus(400, 0);

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_CurrentKeyStatus[key] = action;
}

bool InputHandler::IsKeyPressed(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_PRESS;
}

bool InputHandler::IsKeyDown(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_REPEAT;
}

bool InputHandler::IsKeyReleased(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_RELEASE;
}