#include <QtCore/qdebug.h>

#include <Input/InputManager.h>

namespace TropicalEngine
{

	InputManager::InputManager(void)
	{
		lastMousePosition = glm::vec2(0.0f, 0.0f);
		mousePosition = glm::vec2(0.0f, 0.0f);
	}

	InputManager::~InputManager(void)
	{
		///TODO: implement it.

		while (keyStates.isEmpty() == false)
		{
			delete keyStates.take(keyStates.end().key());
		}
	}

	void InputManager::PressKey(int key)
	{
		if (keyStates.contains(bindings[key]))
		{
			keyStates[bindings[key]]->Press();
		}
	}

	void InputManager::ReleaseKey(int key)
	{
		if (keyStates.contains(bindings[key]))
		{
			keyStates[bindings[key]]->Release();
		}
	}

	void InputManager::Update()
	{
		lastMousePosition = mousePosition;
		for (InputAction* inputAction : keyStates)
		{
			inputAction->Update();
		}
	}

	void InputManager::AddAction(QString actionName)
	{
		if (!keyStates.contains(actionName))
		{
			keyStates[actionName] = new InputAction();
		}
	}

	void InputManager::AddAction(QString actionName, int key)
	{
		AddAction(actionName);
		BindAction(actionName, key);
	}

	void InputManager::BindAction(QString actionName, int key)
	{
		bindings[key] = actionName;
	}

	InputState InputManager::getState(QString actionName)
	{
		if (keyStates.contains(actionName))
		{
			return keyStates[actionName]->getState();
		}
		else
		{
			return InputState::Inactive;
		}
	}

	int InputManager::getTime(QString actionName, int queriedTime)
	{
		if (keyStates.contains(actionName))
		{
			return keyStates[actionName]->getTime(queriedTime);
		}
		else
		{
			return 0;
		}
	}
}