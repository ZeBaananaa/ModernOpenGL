#include "InputHandler.h"
#include "Log.h"

std::vector<int> InputHandler::m_CurrentKeyStatus(400, 0);
std::vector<int> InputHandler::m_MouseButtonKeyStatus(12, 0);
Vector2D InputHandler::mousePos(0.f, 0.f);

InputHandler::~InputHandler()
{
	m_CurrentKeyStatus.clear();
	m_MouseButtonKeyStatus.clear();

	delete &m_CurrentKeyStatus;
	delete &m_MouseButtonKeyStatus;
}

void InputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_CurrentKeyStatus[key] = action;
}

void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	m_MouseButtonKeyStatus[button] = action;
}

void InputHandler::MouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	SetMousePos(xpos, ypos);
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

bool InputHandler::IsMousePressed(int button)
{
	return m_MouseButtonKeyStatus[button] == GLFW_PRESS;
}

bool InputHandler::IsMouseReleased(int button)
{
	return m_MouseButtonKeyStatus[button] == GLFW_RELEASE;
}