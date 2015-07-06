#pragma once
#include <glm.hpp>

#include <QtCore/qmap.h>
#include <QtWidgets/qaction.h>

#include "Camera/CameraComponent.h"
#include "Input/InputAction.h"

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

	int getTime(QString actionName, int queriedTime);

private:
	QMap<QString, InputAction> keyStates;
	QMap<int, QString> bindings;
};