#pragma once
#include <glm.hpp>

#include <QtCore/qhash.h>
#include <QtWidgets/qaction.h>

#include <Camera/CameraComponent.h>

#include "InputAction.h"

namespace TropicalEngine
{

	class InputManager
	{
	public:
		glm::vec2 lastMousePosition;
		glm::vec2 mousePosition;

		InputManager(void);
		~InputManager(void);

		void PressKey(int key);
		void ReleaseKey(int key);
		void Update();

		void AddAction(QString actionName);
		void AddAction(QString actionName, int key);
		void BindAction(QString actionName, int key);

		InputState getState(QString actionName);
		int getTime(QString actionName, int queriedTime);

	private:
		QHash<QString, InputAction*> keyStates;
		QHash<int, QString> bindings;
	};

}