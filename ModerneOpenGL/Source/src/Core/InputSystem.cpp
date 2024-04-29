#include "InputSystem.h"

void InputSystem::Process()
{
}

void InputSystem::AddHandler(InputHandler* inputHandler)
{
	m_handlers.insert(std::make_pair<InputHandler*, InputHandler*>(std::forward<InputHandler*>(inputHandler), std::forward<InputHandler*>(inputHandler)));
}

void InputSystem::RemoveHandler(InputHandler* inputHandler)
{
	std::map<InputHandler*, InputHandler*>::iterator it = m_handlers.find(inputHandler);

	if (it != m_handlers.end())
		m_handlers.erase(it);
}

InputSystem* InputSystem::get()
{
	static InputSystem inputSystem;
	return &inputSystem;
}
