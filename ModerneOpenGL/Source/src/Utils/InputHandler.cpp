#include "Utils/InputHandler.h"
#include "Log.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"

std::vector<int> InputHandler::m_CurrentKeyStatus(400, 0);
std::vector<int> InputHandler::m_MouseButtonKeyStatus(16, 0);
std::vector<int> InputHandler::m_pressedKey;
Vector2D InputHandler::mousePos;
Vector2D InputHandler::wheelPos;
int InputHandler::keyPressed(-1);

void InputHandler::Destroy()
{
	m_CurrentKeyStatus.clear();
	m_MouseButtonKeyStatus.clear();
	m_pressedKey.clear();
}

void InputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!m_pressedKey.empty())
		m_pressedKey.clear(); // Clear list of pressed keys to avoid key being continuously detected

	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

	m_CurrentKeyStatus[key] = action;

	if (action == GLFW_PRESS)
		m_pressedKey.push_back(key);

	keyPressed = key;
}

void InputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	m_MouseButtonKeyStatus[button] = action;
}

void InputHandler::MouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
	SetMousePos(xpos, ypos);
}

void InputHandler::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	SetMouseScrolling(xoffset, yoffset);
}

void InputHandler::ProcessPressedKeys()
{
	for (int key : m_pressedKey)
		m_CurrentKeyStatus[key] = GLFW_REPEAT;
}

bool InputHandler::IsKeyPressed(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_PRESS;
}

bool InputHandler::IsKeyDown(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_REPEAT;
}

bool InputHandler::IsKeyHeld(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_PRESS || m_CurrentKeyStatus[key] == GLFW_REPEAT;
}

bool InputHandler::IsKeyReleased(int key)
{
	return m_CurrentKeyStatus[key] == GLFW_RELEASE;
}

int InputHandler::GetKey()
{
	return keyPressed;
}

bool InputHandler::IsMousePressed(int button)
{
	return m_MouseButtonKeyStatus[button] == GLFW_PRESS;
}

bool InputHandler::IsMouseReleased(int button)
{
	return m_MouseButtonKeyStatus[button] == GLFW_RELEASE;
}

void InputHandler::SetMouseScrolling(double x, double y)
{
	wheelPos.x = static_cast<float>(x);
	wheelPos.y = static_cast<float>(y);
}

Vector2D InputHandler::IsMouseScrolling()
{
	return wheelPos;
}

Vector2D InputHandler::GetMousePos()
{
	return mousePos;
}

void InputHandler::SetMousePos(double x, double y)
{
	mousePos.x = static_cast<float>(x);
	mousePos.y = static_cast<float>(y);
}