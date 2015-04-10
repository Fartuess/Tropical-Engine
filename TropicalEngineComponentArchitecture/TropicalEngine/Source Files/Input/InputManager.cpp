#include "Input/InputManager.h"

InputManager::InputManager(void)
{
	lastMousePosition = glm::vec2(0.0f, 0.0f);
	mousePosition = glm::vec2(0.0f, 0.0f);
}

InputManager::~InputManager(void)
{
	///TODO: implement it.
}

void InputManager::PressKey(int key)
{
	if (keyStates.contains(bindings[key]))
	{
		keyStates[bindings[key]].Press();
	}
}

void InputManager::ReleaseKey(int key)
{
	if (keyStates.contains(bindings[key]))
	{
		keyStates[bindings[key]].Press();
	}
}

void InputManager::Update()
{
	lastMousePosition = mousePosition;
	for (InputAction inputAction : keyStates)
	{
		inputAction.Update();
	}
}

int InputManager::getTime(QString actionName, int queriedTime)
{
	if (keyStates.contains(actionName))
	{
		return keyStates[actionName].getTime(queriedTime);
	}
	else
	{
		return 0;
	}
}