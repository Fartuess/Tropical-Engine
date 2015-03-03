#pragma once
#include <glm.hpp>

#include <QtCore\qmap.h>
#include <QtWidgets\qaction.h>

#include "Camera/CameraComponent.h"

///TODO: Figure out how to implement.

class InputController
{
	struct keyState
	{
		bool W, A, S, D, SPACE, C, UP, LEFT, DOWN, RIGHT;
	};
public:
	glm::vec2 lastMousePosition;
	glm::vec2 mousePosition;
	keyState pressedKeys;

	QMap<Qt::Key, bool> keyStates;
	QMap<Qt::Key, QAction> bindings;

	InputController(void);
	~InputController(void);

	void Update(int deltaTime);
};