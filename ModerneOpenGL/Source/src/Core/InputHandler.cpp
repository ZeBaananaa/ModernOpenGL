#include "InputHandler.h"

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
		m_pressedKey.emplace(key, true);
}

void InputHandler::KeyCallback(int key, int action)
{
}

void Process()
{

}

bool InputHandler::GetKeyPressed(int key)
{
	if (true)
		KeyCallback(key, GLFW_PRESS);
	else
		return;


}

bool InputHandler::GetKeyDown(int key)
{
	if (true)
		KeyCallback(key, GLFW_KEY_DOWN);
	else
		return;
}

std::unordered_map<int, bool> m_pressedKey;