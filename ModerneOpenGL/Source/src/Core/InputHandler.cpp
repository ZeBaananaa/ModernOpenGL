#include "InputHandler.h"
#include "Log.h"
constexpr int INPUTHANDLER_NONE = -1;

std::vector<int> InputHandler::m_CurrentKeyStatus(400, 0);
std::vector<int> InputHandler::m_OldKeyStatus(400, 0);
Vector2D InputHandler::mousePos(0.f, 0.f);

InputHandler::~InputHandler()
{
	m_CurrentKeyStatus.clear();
	m_OldKeyStatus.clear();

	delete &m_CurrentKeyStatus;
	delete &m_OldKeyStatus;
}

void InputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_CurrentKeyStatus[key] = action;
}

void InputHandler::MouseCallback(GLFWwindow* window, double xpos, double ypos)
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

bool InputHandler::IsKeyUnused(int key)
{
	return m_CurrentKeyStatus[key] == INPUTHANDLER_NONE;
}